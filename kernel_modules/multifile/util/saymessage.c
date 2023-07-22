#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");

void say_message(void) 
{
    printk("This is a test message\n");
}


