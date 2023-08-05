#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
//char *p = NULL;

    volatile unsigned char *vaddr = NULL;
static int __init khello_init(void)
{
    int i= 0;
    printk(KERN_EMERG"Hello world1\n");
    if (request_mem_region(0xa0000, 0x1000,"ramtest") < 0)
    {
	printk("Mem reg failed");
    }
    vaddr = ioremap(0xa0000,0x1000);
    if(!vaddr)
    {
	printk("failed to map address\n");
    	release_mem_region(0xa0000, 0x1000);
    }
    
    for(i=0;i<0x100;i+=4)
    {
	        *(vaddr+i)=0xde;
	        *(vaddr+i+1)=0xad;
                *(vaddr+i+2)=0xbe;
                *(vaddr+i+3)=0xef;

    }
    for(i=0;i<0x100;i+=4)
    printk("%x %x\n",(vaddr+i),*(unsigned int*)(vaddr+i));
    return 0; 
}


static void __exit khello_exit(void)
{
	iounmap((void*)vaddr);
    	release_mem_region(0xa0000, 0x1000);
    printk("Khello unloaded.\n");
}

module_init(khello_init);
module_exit(khello_exit); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A simple Hello world module.");


