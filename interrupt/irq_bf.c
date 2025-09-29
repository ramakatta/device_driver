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
#include <asm/io.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>

MODULE_AUTHOR("Rama Krishna");
MODULE_LICENSE("GPL");
#define LOCAL_IRQ_NO 1
void do_mytasklet (struct tasklet_struct *unused);
void do_mywork(struct work_struct *data);
DECLARE_TASKLET (my_tasklet, do_mytasklet);
DECLARE_WORK(my_work, do_mywork);
static int isrCnt = 0;
static int my_devid;
void do_mytasklet(struct tasklet_struct *unused)
{
printk("*************This message from tasklet****************\n");
printk("tasklet-in_interrupt: %d\n", in_interrupt());
printk("tasklet-in_irq : %d\n", in_irq());
}
/*******************************************************************************
* Name:do_mywork
*******************************************************************************/
void do_mywork (struct work_struct *data)
{
printk("This message from work handler\n");
printk("work-in_interrupt: %d\n", in_interrupt());
printk("work-in_irq : %d\n", in_irq());
}
/*******************************************************************************
* Name:myIntHandler
*******************************************************************************/
static irqreturn_t isr_routine(int irq, void *dev_id)
{
printk("**********************FROM HARD IRQ***************\n");
printk("in_interrupt: %d\n", in_interrupt());
printk("in_irq : %d\n", in_irq());
printk("Happy days\n");
//tasklet_schedule(&my_tasklet);
#if 1 
schedule_work(&my_work);
isrCnt++;
#endif
return IRQ_HANDLED;
}



/*******************************************************************************
* Name: init_module
*******************************************************************************/
int init_module(void)
{
   int res;
   int retval;
    if(request_irq(LOCAL_IRQ_NO,isr_routine,IRQF_SHARED,"irq0",&my_devid))
    {
	printk("can't get interrupt:%x\n",LOCAL_IRQ_NO);
	goto fail_exit1;
    }

     printk("Interrupt installed sucessfully\n");
     return 0;

fail_exit1:
    return -1;
}

/*******************************************************************************
* Name:cleanup_module
*******************************************************************************/
void cleanup_module(void)
{
free_irq(LOCAL_IRQ_NO,&my_devid);
printk(KERN_ALERT "char dev unloaded successfully \n");
}

