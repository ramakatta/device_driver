/***************************************************************************//**
*  \file       driver.c
*
*  \details    Simple Linux device driver (Real Linux Device Driver)
*
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/err.h>

#define mem_size        1024           //Memory Size

#define NUM_SAMP_DEVS  4
#define MAX_BUF_SIZE   64
#define MINOR_START    3

 

struct sdev_dev
{
  
  uint8_t kernel_buffer[512];
  char    name[16];
  struct  cdev cdev;               /* The cdev structure */
}*sdev_devp;

struct sdev_dev *sdev_devps[NUM_SAMP_DEVS];

struct class *dev_class;
dev_t sdev_dev_number;

#define DEVICE_NAME                 "myetxdev"

/*
** Function Prototypes
*/
static int      __init etx_driver_init(void);
static void     __exit etx_driver_exit(void);
static int      etx_open(struct inode *inode, struct file *file);
static int      etx_release(struct inode *inode, struct file *file);
static ssize_t  etx_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  etx_write(struct file *filp, const char *buf, size_t len, loff_t * off);


/*
** File Operations structure
*/
static struct file_operations sdev_fops =
{
        .owner          = THIS_MODULE,
        .read           = etx_read,
        .write          = etx_write,
        .open           = etx_open,
        .release        = etx_release,
};
 
/*
** This function will be called when we open the Device file
*/
static int etx_open(struct inode *inode, struct file *file)
{
    struct sdev_dev *sdevp;

    int major;
    int minor;

    major = imajor(inode);
    minor = iminor(inode);
    printk("instanse minor number:%d\n",minor);

    sdevp =   sdev_devps[minor -  MINOR_START];
    file->private_data = sdevp;

    pr_info("Device File Opened...!!!\n");
        return 0;
}

/*
** This function will be called when we close the Device file
*/
static int etx_release(struct inode *inode, struct file *file)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}

/*
** This function will be called when we read the Device file
*/
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	struct sdev_dev *sdevp;
	sdevp = file->private_data;
        //Copy the data from the kernel space to the user-space
        if( copy_to_user(buf, sdevp->kernel_buffer, mem_size) )
        {
                pr_err("Data Read : Err!\n");
        }
        pr_info("Data Read : Done!\n");
        return mem_size;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	struct sdev_dev *sdevp;
	sdevp = file->private_data;

        //Copy the data to kernel space from the user-space
        if( copy_from_user(sdevp->kernel_buffer, buf, len) )
        {
                pr_err("Data Write : Err!\n");
        }
        pr_info("Data Write : Done!\n");
        return len;
}

/*
** Module Init function
*/
static int __init etx_driver_init(void)
{
	int i;
        /*Allocating Major number*/
	 if (alloc_chrdev_region(&sdev_dev_number, MINOR_START,
                            NUM_SAMP_DEVS, DEVICE_NAME) < 0)
  	{
    		printk(KERN_DEBUG "Can't register device\n");
    		return -1;
  	}

        pr_info("Major = %d Minor = %d \n",MAJOR(sdev_dev_number), MINOR(sdev_dev_number));
        /*Creating struct class*/
        if(IS_ERR(dev_class = class_create(THIS_MODULE, DEVICE_NAME))){
            pr_info("Cannot create the struct class\n");
            goto r_class;
        }

	for (i=0; i<NUM_SAMP_DEVS; i++)
  	{
    		/* Allocate memory for the per-device structure */
    		sdev_devp = kmalloc(sizeof(struct sdev_dev), GFP_KERNEL);
    		if (!sdev_devp)
    		{
      			printk("Bad Kmalloc\n"); return -ENOMEM;
    		}

		sprintf(sdev_devp->name, "mysdev%d",i);
   
	       	/* Connect the file operations with the cdev */
    		cdev_init(&sdev_devp->cdev, &sdev_fops);
    		sdev_devp->cdev.owner = THIS_MODULE;
 
	        /*Adding character device to the system*/
        	if((cdev_add(&sdev_devp->cdev, (sdev_dev_number + i),1)) < 0){
            		pr_info("Cannot add the device to the system\n");
        	}
	 
        	/*Creating device*/
        	device_create(dev_class,NULL,(sdev_dev_number + i), NULL, "etx_dev%d", i);
		sdev_devps[i] = sdev_devp;
	}
        
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
r_class:
        unregister_chrdev_region(sdev_dev_number,NUM_SAMP_DEVS);
        return -1;
}

/*
** Module exit function
*/
static void __exit etx_driver_exit(void)
{
   int i;

  /* Release the major number */
  unregister_chrdev_region((sdev_dev_number), NUM_SAMP_DEVS);

  for (i=0; i<NUM_SAMP_DEVS; i++)
  {
    device_destroy(dev_class, sdev_dev_number + i);
    cdev_del(&sdev_devps[i]->cdev);
    kfree(sdev_devps[i]);
  }
  class_destroy(dev_class);
  return;
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("Simple Linux device driver (Real Linux Device Driver)");
MODULE_VERSION("1.4");
