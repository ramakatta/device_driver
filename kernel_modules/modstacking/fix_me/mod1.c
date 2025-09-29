#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Module 1: Demonstrating namespace pollution");

int counter = 10;   // global symbol (bad practice!)
EXPORT_SYMBOL(counter);		   

static int __init mod1_init(void)
{
    printk(KERN_INFO "mod1: loaded, counter = %d\n", counter);
    return 0;
}

static void __exit mod1_exit(void)
{
    printk(KERN_INFO "mod1: unloaded\n");
}

module_init(mod1_init);
module_exit(mod1_exit);

