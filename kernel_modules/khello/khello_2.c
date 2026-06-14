#include <linux/module.h>
#include <linux/kernel.h>

static int count = 100;
static int __initdata test = 3;

static  int __init khello_init(void)
{
    printk(KERN_EMERG"Hello world\n");
    pr_emerg("Hello world1\n");
    pr_emerg("count:%d\n",count);
    pr_emerg("test:%d\n",test);
    return 0;
}

static void __exit khello_exit(void)
{
    pr_emerg("count:%d\n",count);
    printk(KERN_EMERG"Bye world\n");

}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rama");
MODULE_DESCRIPTION("Hello world module");

module_init(khello_init);
module_exit(khello_exit);
