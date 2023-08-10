#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/sched.h>

#define GPIO_REG_BASE 0x7e200000
#define GPIO_REG_LEN 164
static void __iomem *iobase;

static int gpio_init(void)
{
	if (!request_mem_region(GPIO_REG_BASE, GPIO_REG_LEN, "mydriver")) {
		printk("couldn't get region for MMIO, aborting\n");
		return -EBUSY; // or -EINVAL, as appropriate
	}
	iobase = ioremap(GPIO_REG_BASE, GPIO_REG_LEN);
	if (!iobase)  {
        	//iounmap(iobase);
		release_mem_region(GPIO_REG_BASE, GPIO_REG_LEN);
	}
	printk("iobase:%x\n",*(char*)(iobase+18));
	return 0;
}

static void gpio_exit(void)
{
    iounmap(iobase);
    release_mem_region(GPIO_REG_BASE, GPIO_REG_LEN);
    printk("memory io unloaded.\n");
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A simple memory mapping module.");

