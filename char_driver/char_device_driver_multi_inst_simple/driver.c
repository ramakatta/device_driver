#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/pci.h>

#include <linux/poll.h>
#include <linux/ioport.h>
#include <linux/errno.h>

#define NUM_SAMP_DEV 4
#define MINOR_START 60
#define BUFFER_SIZE 1024

struct sdev_dev
{
   char name[16];
   struct cdev cdev;
   char kernel_buffer[1024];
}*sdev_devp;

struct sdev_dev *sdev_devps[NUM_SAMP_DEV];

struct class *myclass;

int sdev_open(struct inode *inode, struct file *file);
int sdev_release(struct inode *inode, struct file *file);
ssize_t sdev_read(struct file *file, char *buf, size_t count, loff_t *ppos);
ssize_t sdev_write(struct file *file, const char *buf, size_t count,
                                                            loff_t *ppos);



/* File operations structure. Defined in linux/fs.h */
static struct file_operations sdev_fops =
{
    .owner   = THIS_MODULE,         /* Owner */
    .open    = sdev_open,           /* Open method */
    .release = sdev_release,        /* Release method */
    .read    = sdev_read,           /* Read method */
    .write   = sdev_write,          /* Write method */
};


static dev_t sdev_dev_number;       /* Allotted device number */

#define DEVICE_NAME                 "mysdev"

int __init sdev_init(void)
{
  int i, ret;
  if (alloc_chrdev_region(&sdev_dev_number, MINOR_START,NUM_SAMP_DEV, DEVICE_NAME)<0)
  {
      printk(KERN_DEBUG "Can't register device\n");
      return -1;
  }
  printk(KERN_DEBUG "Major : %u\n", MAJOR(sdev_dev_number));
  printk(KERN_DEBUG "Minor : %u\n", MINOR(sdev_dev_number));

  myclass = class_create(DEVICE_NAME);

  for (i=0; i<NUM_SAMP_DEV; i++)
  {
      sdev_devp = kmalloc(sizeof(struct sdev_dev),GFP_KERNEL);
      if(!sdev_devp)
      {
                printk("Bad Kmalloc\n"); return -ENOMEM;
       }

       sprintf(sdev_devp->name, "mysdev%d",i);
       cdev_init(&sdev_devp->cdev, &sdev_fops);
       sdev_devp->cdev.owner = THIS_MODULE;
      /* Connect the major/minor number to the cdev */
       ret = cdev_add(&sdev_devp->cdev, (sdev_dev_number + i), 1);
       if (ret)
       {
          printk("Bad cdev\n");
          return ret;
       }

      device_create(myclass, NULL, (sdev_dev_number + i), NULL, "mysdev%d", i);
      sdev_devps[i] = sdev_devp;
  } 
     printk("SDEV Driver Initialized.\n");
     return 0;

}

void __exit sdev_cleanup(void)
{
  int i;

  for (i=0; i<NUM_SAMP_DEV; i++)
  {
    device_destroy(myclass, sdev_dev_number + i);
    cdev_del(&sdev_devps[i]->cdev);
    kfree(sdev_devps[i]);
  }
  class_destroy(myclass);

  /* Release the major number */
  unregister_chrdev_region((sdev_dev_number), NUM_SAMP_DEV);

  return;
}


/* Open sample device */
int sdev_open(struct inode *inode, struct file *file)
{
#if 0
    struct sdev_dev *sdevp;

    int major;
    int minor;

    major = imajor(inode);
    minor = iminor(inode);
 
   printk("instanse minor number:%d\n",minor);
   sdevp =   sdev_devps[minor -  MINOR_START];

    /* Easy access to sdev_devp from rest of the entry points */
    file->private_data = sdevp;
#endif
    dump_stack();
    file->private_data = container_of(inode->i_cdev, struct sdev_dev, cdev);
    return 0;
}

/******** Release sample device ********/
int sdev_release(struct inode *inode, struct file *file)
{
    //struct sdev_dev *sdev_devp = file->private_data;

    /* Reset file pointer */

    return 0;
}


/********** Write to a sample device ***********/
ssize_t sdev_write(struct file *file, const char *buf, size_t count,
                                                             loff_t *ppos)
{
  struct sdev_dev *tdev = file->private_data;
  //Copy the data to kernel space from the user-space
        if( copy_from_user(tdev->kernel_buffer, buf, count) )
        {
                pr_err("Data Write : Err!\n");
        }
        pr_info("Data Write : Done!\n");
        return count;
}

/******* Read from a sample device  *********/
ssize_t sdev_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
    struct sdev_dev *tdev = file->private_data;
         //Copy the data from the kernel space to the user-space
        if( copy_to_user(buf, tdev->kernel_buffer, count) )
        {
                pr_err("Data Read : Err!\n");
        }
        pr_info("Data Read : Done!\n");
        return count;
}
module_init(sdev_init);
module_exit(sdev_cleanup);

MODULE_LICENSE("GPL");


