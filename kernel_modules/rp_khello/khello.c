#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
static int hello = 3;
static int __init khello_init(void)
{
    printk(KERN_EMERG"Hello world1\n");
    printk("Hello world2\n");
    printk("Hello world3\n");
    hello=99;
    printk("pid:%x comm:%s state:%d jiffies:%lu %d\n",current->pid,current->comm,current->__state,jiffies,hello);
    return 0; 
}
static void __exit khello_exit(void)
{
    printk("Khello unloaded.%d\n");
}
module_init(khello_init);
module_exit(khello_exit); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A simple Hello world module.");


