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
static int mydev_open(struct inode *inode, struct file *file);
static int mydev_close(struct inode *inode, struct file *file);
static int mydev_poll(struct file *file,poll_table *wait);




MODULE_AUTHOR("Rama Krishna");
MODULE_LICENSE("GPL");
#define LOCAL_IRQ_NO 1

struct myadvdev
{
  struct cdev mycdev;
};

wait_queue_head_t wq;
struct class *myclass;
dev_t mydevno;
static struct  task_struct *ts;
struct myadvdev mydevcb;
struct fasync_struct *async_queue;
//void do_mytasklet(void *data);
//DECLARE_TASKLET(my_tasklet,do_mytasklet,0);

#define MYDEV_NO_DEVS 1
#define MYDEV_NAME "myadvdev"
static struct file_operations mydev_ops =
{
.open = mydev_open,
.release = mydev_close,
.poll = mydev_poll,
};

static atomic_t data_ready;
static int my_devid;
static irqreturn_t isr_routine(int irq,void *dev_id)
{
  atomic_set (&data_ready, 1);
  //tasklet_schedule(&my_tasklet);
  printk("FRom ISR\n");
  wake_up_interruptible(&wq);
  return IRQ_HANDLED;
}
static int mydev_open(struct inode *inode, struct file * file)
{
 struct myadvdev *pcb;
 pcb = container_of(inode->i_cdev, struct myadvdev, mycdev);
 file->private_data = pcb;
return 0;
}

static int mydev_close(struct inode *inode, struct file * file)
{
printk("<1>" "device closed\n");
return 0;
}
static int mydev_poll(struct file * file,poll_table *wait)
{
   unsigned int mask = 0;
   printk("Poll called\n");
   poll_wait(file,&wq,wait);
   if(atomic_read (&data_ready))
   {
    mask = POLLIN | POLLRDNORM;
    atomic_set (&data_ready, 0);
   }
   return mask;
}


/*******************************************************************************
* Name: init_module
*******************************************************************************/
int init_module(void)
{
   int res;
   int retval;
   res = alloc_chrdev_region(&mydevno, 0, MYDEV_NO_DEVS, MYDEV_NAME);
   if(res<0)
   {
	printk("<1>" "Registration Error %d\n",res);
	return res;
   }
   else 
   {
	printk("<1>" "Registration success %d\n",res);
   }

   myclass = class_create(THIS_MODULE, MYDEV_NAME);

   init_waitqueue_head(&wq);
   cdev_init(&mydevcb.mycdev, &mydev_ops);
   mydevcb.mycdev.owner = THIS_MODULE;
   res = cdev_add(&mydevcb.mycdev, mydevno, 1);

   if(res)
      goto fail_exit;
      printk("cdev added successully %d\n",res);
      device_create(myclass, NULL, mydevno, NULL, MYDEV_NAME);
      
    if(request_irq(LOCAL_IRQ_NO,isr_routine,IRQF_SHARED,"irq0",&my_devid))
    {
	printk("can't get interrupt:%x\n",LOCAL_IRQ_NO);
	goto fail_exit1;
    }

     printk("Interrupt installed sucessfully\n");
     return 0;

 fail_exit:
 cdev_del(&mydevcb.mycdev);
 unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
 device_destroy(myclass, mydevno);
 class_destroy(myclass);
 return res;
 fail_exit1:
 cdev_del(&mydevcb.mycdev);
 unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
 device_destroy(myclass, mydevno);
 class_destroy(myclass);
 return res;
}

/*******************************************************************************
* Name:cleanup_module
*******************************************************************************/
void cleanup_module(void)
{
kthread_should_stop();
cdev_del(&mydevcb.mycdev);
unregister_chrdev_region(mydevno, MYDEV_NO_DEVS);
device_destroy(myclass, mydevno);
class_destroy(myclass);
free_irq(LOCAL_IRQ_NO,&my_devid);
printk(KERN_ALERT "char dev unloaded successfully \n");
}

