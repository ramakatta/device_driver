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
#include <linux/proc_fs.h>  /* procfs APIs etc */
#include <linux/seq_file.h>

#define mem_size        2048           //Memory Size
 
dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
static uint8_t *kernel_buffer = NULL;
DEFINE_MUTEX(mtx);

#define	PROC_FILE		"xml_config"
#define	PROC_FILE_PERMS	        0666
#define	OURMODNAME		"procfs_xml_config"

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
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = etx_read,
        .write          = etx_write,
        .open           = etx_open,
        .release        = etx_release,
};

static int proc_show_xml_config(struct seq_file *seq, void *v)
{
	    
	if (mutex_lock_interruptible(&mtx))
		return -ERESTARTSYS;
	seq_printf(seq, "xml_config:%s\n",kernel_buffer);
	mutex_unlock(&mtx);
	return 0;
}
 
/*
** This function will be called when we open the Device file
*/
static int etx_open(struct inode *inode, struct file *file)
{
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
	if (mutex_lock_interruptible(&mtx))
		return -ERESTARTSYS;
        //Copy the data from the kernel space to the user-space
        if( copy_to_user(buf, kernel_buffer, mem_size) )
        {
                pr_err("Data Read : Err!\n");
        }
	mutex_unlock(&mtx);
        pr_info("Data Read : Done!\n");
        return mem_size;
}

/*
** This function will be called when we write the Device file
*/
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	if (mutex_lock_interruptible(&mtx))
		return -ERESTARTSYS;
        //Copy the data to kernel space from the user-space
        if( copy_from_user(kernel_buffer, buf, len) )
        {
                pr_err("Data Write : Err!\n");
        }
	mutex_unlock(&mtx);
        pr_info("Data Write : Done!\n");
        return len;
}

static struct proc_dir_entry *gprocdir;

/*
** Module Init function
*/
static int __init etx_driver_init(void)
{
	int stat;
	if (unlikely(!IS_ENABLED(CONFIG_PROC_FS))) {
		pr_warn("procfs unsupported! Aborting ...\n");
		return -EINVAL;
	}

        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
                pr_info("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&etx_cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&etx_cdev,dev,1)) < 0){
            pr_info("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if(IS_ERR(dev_class = class_create("etx_class"))){
            pr_info("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if(IS_ERR(device_create(dev_class,NULL,dev,NULL,"etx_device"))){
            pr_info("Cannot create the Device 1\n");
            goto r_device;
        }
        
        /*Creating Physical memory*/
        if((kernel_buffer = kmalloc(mem_size , GFP_KERNEL)) == 0){
            pr_info("Cannot allocate memory in kernel\n");
            goto r_device;
        }

	gprocdir = proc_mkdir(OURMODNAME, NULL);
	if (!gprocdir) {
		pr_warn("proc_mkdir failed, aborting...\n");
		stat = -ENOMEM;
		goto r_class;
	}
	pr_debug("proc dir (/proc/%s) created\n", OURMODNAME);

	if (!proc_create_single_data(PROC_FILE, PROC_FILE_PERMS,
					gprocdir, proc_show_xml_config, 0)) {
		pr_warn("proc_create failed, aborting...\n");
		stat = -ENOMEM;
		goto r_device;
	}
        
        strcpy(kernel_buffer, "Data not yet available");
        
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
r_device:
        class_destroy(dev_class);
	remove_proc_subtree(OURMODNAME, NULL);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

/*
** Module exit function
*/
static void __exit etx_driver_exit(void)
{
	kfree(kernel_buffer);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
	remove_proc_subtree(OURMODNAME, NULL);
        pr_info("Device Driver Remove...Done!!!\n");
}
 
module_init(etx_driver_init);
module_exit(etx_driver_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("Simple Linux device driver (Real Linux Device Driver)");
MODULE_VERSION("1.4");
