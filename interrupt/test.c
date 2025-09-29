#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

#define LOCAL_IRQ 1
static int dev_id;

void do_mywork(struct work_struct *data);
DECLARE_WORK(my_work, do_mywork);

MODULE_AUTHOR("Rama Krishna");
MODULE_LICENSE("GPL");

void do_mywork (struct work_struct *data)
{
printk("This message from work handler\n");
printk("work-in_interrupt: %d\n", in_interrupt());
printk("work-in_irq : %d\n", in_irq());
printk("work-in_task : %d\n", in_task());

}


static irqreturn_t isr_routine(int irq, void *dev)
{
   printk("Happy days..IRQ");
   printk("in_task: %d\n", in_task());
   printk("in_irq : %d\n", in_irq());
   schedule_work(&my_work);
   
   return IRQ_HANDLED;
 }



int init_module(void)
{
   if(request_irq(LOCAL_IRQ, isr_routine, IRQF_SHARED, "irq0", &dev_id))
    {
        printk("request_irq failed");
        return -1;
     }
     printk("in_task: %d\n", in_task());

     return 0;
 
}

void cleanup_module(void)
{
    free_irq(LOCAL_IRQ, &dev_id);

}
