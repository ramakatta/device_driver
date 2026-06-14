#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/ioport.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/interrupt.h> 
#include <linux/device.h>

MODULE_AUTHOR("Rama Krishna");
MODULE_DESCRIPTION("Threaded IRQ Refactored Driver");
MODULE_LICENSE("GPL");

#define LOCAL_IRQ_NO 1
#define MYDEV_NO_DEVS 1
#define MYDEV_NAME "myadvdev"

struct myadvdev {
    struct cdev mycdev;
};

static struct class *myclass;
static dev_t mydevno;
static struct myadvdev mydevcb;
static struct fasync_struct *async_queue;
static int my_devid;

/**
 * 1. Top-Half ISR (Hard IRQ Context)
 * Runs immediately when the interrupt fires. Must be lightning fast.
 */
static irqreturn_t my_top_half_isr(int irq, void *dev_id)
{
    /* 
     * NOTE: In a shared IRQ configuration, you MUST check your hardware status
     * register here. If your hardware didn't fire, return IRQ_NONE immediately.
     */
    
    // Returning IRQ_WAKE_THREAD tells the OS to run the bottom-half thread handler.
    return IRQ_WAKE_THREAD;
}

/**
 * 2. Bottom-Half Threaded Handler (Process Context)
 * Called automatically by the kernel in a dedicated thread. Blocking is allowed here.
 */
static irqreturn_t my_threaded_bh_handler(int irq, void *dev_id)
{
    /* This replaces your old tasklet execution frame AND kthread loop */
    if (async_queue) {
        kill_fasync(&async_queue, SIGIO, POLL_IN);
    }
    
    return IRQ_HANDLED;
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
    /* Prevent user-after-free by destroying asynchronous queues on close */
    mydev_fasync(-1, file, 0);
    return 0;
}

static struct file_operations mydev_ops = {
    .owner   = THIS_MODULE,
    .open    = mydev_open,
    .release = mydev_close,
    .fasync  = mydev_fasync,
};

static int __init my_init_module(void)
{
    int res;

    res = alloc_chrdev_region(&mydevno, 0, MYDEV_NO_DEVS, MYDEV_NAME);
    if (res < 0) {
        pr_err("Registration Error %d\n", res);
        return res;
    }

    myclass = class_create(MYDEV_NAME);
    if (IS_ERR(myclass)) {
        res = PTR_ERR(myclass);
        goto fail_unregister_region;
    }

    cdev_init(&mydevcb.mycdev, &mydev_ops);
    res = cdev_add(&mydevcb.mycdev, mydevno, 1);
    if (res)
        goto fail_destroy_class;
   
    if (IS_ERR(device_create(myclass, NULL, mydevno, NULL, MYDEV_NAME))) {
        res = -ENOMEM;
        goto fail_del_cdev;
    }

    /* 
     * 3. Registering the Threaded IRQ
     * Replaces request_irq(), tasklet_init(), and kthread_run().
     */
    res = request_threaded_irq(LOCAL_IRQ_NO, 
                               my_top_half_isr,       // Top-half (Hard IRQ)
                               my_threaded_bh_handler,// Bottom-half (Threaded)
                               IRQF_SHARED,           // Interrupt flags
                               "my_threaded_device",  // /proc/interrupts identifier
                               &my_devid);            // Unique token for shared line
    if (res) {
        pr_err("Failed to request threaded IRQ: %d\n", res);
        goto fail_destroy_device;
    }

    return 0;

fail_destroy_device:
    device_destroy(myclass, mydevno);
fail_del_cdev:
    cdev_del(&mydevcb.mycdev);
fail_destroy_class:
    class_destroy(myclass);
fail_unregister_region:
    unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
    return res;
}

static void __exit my_cleanup_module(void)
{
    /* 
     * CRITICAL: free_irq guarantees both the top-half stops executing AND 
     * the companion bottom-half kernel thread is cleanly exited/joined.
     */
    free_irq(LOCAL_IRQ_NO, &my_devid);
    
    device_destroy(myclass, mydevno);
    cdev_del(&mydevcb.mycdev);
    class_destroy(myclass);
    unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
    
    pr_info("Driver unloaded cleanly.\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);
