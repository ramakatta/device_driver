#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Module 2: Demonstrating namespace pollution");

int counter = 99;   // SAME NAME as in mod1.c → namespace pollution!
EXPORT_SYMBOL(counter);		   

static int __init mod2_init(void)
{
    printk(KERN_INFO "mod2: loaded, counter = %d\n", counter);
    return 0;
}

static void __exit mod2_exit(void)
{
    printk(KERN_INFO "mod2: unloaded\n");
}

module_init(mod2_init);
module_exit(mod2_exit);

