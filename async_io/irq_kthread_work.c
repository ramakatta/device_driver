#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/ioport.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/pci.h>
#include <linux/kthread.h> 
#include <linux/interrupt.h> 
#include <linux/device.h>

static int mydev_open(struct inode *inode, struct file *file);
static int mydev_close(struct inode *inode, struct file *file);
static int mydev_fasync(int fd, struct file *fp, int mode);

MODULE_AUTHOR("Rama Krishna");
MODULE_LICENSE("GPL");

#define LOCAL_IRQ_NO 1
#define MYDEV_NO_DEVS 1
#define MYDEV_NAME "myadvdev"

struct myadvdev {
    struct cdev mycdev;
};

static wait_queue_head_t wq;
static struct class *myclass;
static struct tasklet_struct my_tasklet;
static dev_t mydevno;
static struct task_struct *ts;
static struct myadvdev mydevcb;
static struct fasync_struct *async_queue;

static struct file_operations mydev_ops = {
    .owner   = THIS_MODULE,
    .open    = mydev_open,
    .release = mydev_close,
    .fasync  = mydev_fasync,
};

static atomic_t data_ready = ATOMIC_INIT(0);
static int my_devid;

static irqreturn_t isr_routine(int irq, void *dev_id)
{
    /* Note: If sharing an IRQ line, verify your hardware's status register here */
    atomic_set(&data_ready, 1);
    tasklet_schedule(&my_tasklet);
    return IRQ_HANDLED;
}

/* Legacy/Older Signature handler match for tasklet_init */
void do_mytasklet(unsigned long data)
{
    wake_up_interruptible(&wq);
}

static int mydev_open(struct inode *inode, struct file *file)
{
    struct myadvdev *pcb = container_of(inode->i_cdev, struct myadvdev, mycdev);
    file->private_data = pcb;
    return 0;
}

static int mydev_fasync(int fd, struct file *fp, int mode)
{
    return fasync_helper(fd, fp, mode, &async_queue);
}

static int mydev_close(struct inode *inode, struct file *file)
{
    /* FIX 3: Detach from fasync queue to prevent dangling pointers on close */
    mydev_fasync(-1, file, 0);
    return 0;
}

int kthread_fct(void *data)
{
    while (!kthread_should_stop()) {
        /* FIX 2: Added kthread_should_stop check inside the wait macro */
        wait_event_interruptible(wq, (atomic_read(&data_ready) != 0) || kthread_should_stop());
        
        if (kthread_should_stop())
            break; /* FIX 1: Safely break instead of using destructive do_exit(0) */

        atomic_set(&data_ready, 0);

        if (async_queue) {
            kill_fasync(&async_queue, SIGIO, POLL_IN);
        }
    } 
    return 0;
}

int init_module(void)
{
    int res;

    init_waitqueue_head(&wq);
    tasklet_init(&my_tasklet, do_mytasklet, 0);

    res = alloc_chrdev_region(&mydevno, 0, MYDEV_NO_DEVS, MYDEV_NAME);
    if (res < 0) {
        pr_err("Registration Error %d\n", res);
        return res;
    }

    /* Target appropriate class_create call signature matching your build environment */
    myclass = class_create(THIS_MODULE, MYDEV_NAME);
    if (IS_ERR(myclass)) {
        res = PTR_ERR(myclass);
        goto fail_unregister;
    }

    cdev_init(&mydevcb.mycdev, &mydev_ops);
    mydevcb.mycdev.owner = THIS_MODULE;
    res = cdev_add(&mydevcb.mycdev, mydevno, 1);
    if (res)
        goto fail_destroy_class;

    if (IS_ERR(device_create(myclass, NULL, mydevno, NULL, MYDEV_NAME))) {
        res = -ENOMEM;
        goto fail_del_cdev;
    }
      
    ts = kthread_run(kthread_fct, NULL, "eint_kthread");
    if (IS_ERR(ts)) {
        res = PTR_ERR(ts);
        goto fail_destroy_device;
    }  

    res = request_irq(LOCAL_IRQ_NO, isr_routine, IRQF_SHARED, "irq0", &my_devid);
    if (res) {
        goto fail_stop_kthread;
    }

    return 0;

/* Clean, step-by-step unrolling of failed init targets */
fail_stop_kthread:
    kthread_stop(ts);
fail_destroy_device:
    device_destroy(myclass, mydevno);
fail_del_cdev:
    cdev_del(&mydevcb.mycdev);
fail_destroy_class:
    class_destroy(myclass);
fail_unregister:
    unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
    return res;
}

void cleanup_module(void)
{
    /* FIX: Always free hardware hooks (IRQ) BEFORE breaking infrastructure down */
    free_irq(LOCAL_IRQ_NO, &my_devid);
    
    if (ts) {
        kthread_stop(ts);
    }

    tasklet_kill(&my_tasklet);
    device_destroy(myclass, mydevno);
    cdev_del(&mydevcb.mycdev);
    class_destroy(myclass);
    unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
    
    pr_alert("char dev unloaded successfully\n");
}
