#include <linux/module.h>
#include <linux/kernel.h>

char *msg="rama";
unsigned short io=5;
unsigned short status=0;

static int __init khello_init(void) {

    printk("Greeting message: %s, io address: %x\n", msg, io);
    printk("string length:%lu\n",strlen(msg));
    printk("status:%x\n",status);
    return 0;
}

static void __exit khello_exit(void) {
    printk("Goodbye...\n");
}

module_init(khello_init);
module_exit(khello_exit);

module_param(msg, charp, S_IRUGO);
module_param(io, ushort, S_IRUGO);
module_param(status, ushort, S_IRUGO);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A simple Hello world module.");
MODULE_PARM_DESC(msg, "Greeting message string...");
MODULE_PARM_DESC(io, "I/O base address");
MODULE_PARM_DESC(status, "status flag");


