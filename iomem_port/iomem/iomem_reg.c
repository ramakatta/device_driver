/* According to ACPI v4.0 spec */
 
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/ioport.h>
#include <linux/io.h>
#define VIDEO_RAM_BASE 0xA0000 
#define VIDEO_RAM_SIZE 0x20000 
 
volatile unsigned char *vaddr = NULL;
 
static int __init iomem_init(void)
{
    unsigned long i= 0;
    printk("IOMEM loaded\n");
    if (request_mem_region(VIDEO_RAM_BASE, VIDEO_RAM_SIZE,"VideoRAM") < 0)
    {
	printk("Mem reg failed");
    }
    vaddr = ioremap(VIDEO_RAM_BASE,VIDEO_RAM_SIZE);
    if(!vaddr)
    {
	printk("failed to map address\n");
    	release_mem_region(VIDEO_RAM_BASE,VIDEO_RAM_SIZE);
        return -1;
    }
    for(i=0;i<0x10;i++)
    printk("%x %x\n",vaddr+i,*(vaddr+i));
    
    return 0; 
}

static void __exit iomem_exit(void)
{
        if(vaddr)
	iounmap((void*)vaddr);
    	release_mem_region(VIDEO_RAM_BASE,VIDEO_RAM_SIZE);
        printk("IOMEM unloaded.\n");
}

module_init(iomem_init);
module_exit(iomem_exit); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A simple IOMMEM module.");


