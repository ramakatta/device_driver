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

#define NUM_SAMP_DEVS  4
#define MAX_BUF_SIZE   64
#define MINOR_START    3

int sdev_open(struct inode *inode, struct file *file);
int sdev_release(struct inode *inode, struct file *file);
ssize_t sdev_read(struct file *file, char *buf, size_t count, loff_t *ppos);
ssize_t sdev_write(struct file *file, const char *buf, size_t count, 
                                                            loff_t *ppos);

struct cirq
{
  unsigned char buf[MAX_BUF_SIZE];
  int           rdix;
  int           wrix;
  int           cnt;
};

/* Per-device structure */
struct sdev_dev 
{
  struct cirq cque;
  char        name[16];
  struct cdev cdev;               /* The cdev structure */

} *sdev_devp;

struct sdev_dev *sdev_devps[NUM_SAMP_DEVS];

struct class *myclass;

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

/*
 * Driver Initialization
 */
int __init sdev_init(void)
{
  int i, ret;

  /* Request dynamic allocation of a device major number */
  if (alloc_chrdev_region(&sdev_dev_number, MINOR_START,
                            NUM_SAMP_DEVS, DEVICE_NAME) < 0) 
  {
    printk(KERN_DEBUG "Can't register device\n"); 
    return -1;
  }

  printk(KERN_DEBUG "Major : %u\n", MAJOR(sdev_dev_number)); 
  printk(KERN_DEBUG "Minor : %u\n", MINOR(sdev_dev_number)); 

  myclass = class_create(DEVICE_NAME);
  for (i=0; i<NUM_SAMP_DEVS; i++) 
  {
    /* Allocate memory for the per-device structure */
    sdev_devp = kmalloc(sizeof(struct sdev_dev), GFP_KERNEL);
    if (!sdev_devp) 
    {
      printk("Bad Kmalloc\n"); return -ENOMEM;
    }

    /* initialize the circular queue */
    sdev_devp->cque.rdix = 0;
    sdev_devp->cque.wrix = 0;
    sdev_devp->cque.cnt  = 0;

    sprintf(sdev_devp->name, "mysdev%d",i);
    /* Connect the file operations with the cdev */
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

  /* Release the major number */
  unregister_chrdev_region((sdev_dev_number), NUM_SAMP_DEVS);

  for (i=0; i<NUM_SAMP_DEVS; i++) 
  {
    device_destroy(myclass, sdev_dev_number + i);
    cdev_del(&sdev_devps[i]->cdev);
    kfree(sdev_devps[i]);
  }
  class_destroy(myclass);
  return;
}


/* * Open sample device */
int sdev_open(struct inode *inode, struct file *file)
{
#if 0
    struct sdev_dev *sdevp;

    int major;
    int minor;

    major = imajor(inode);
    minor = iminor(inode);
    printk("instanse minor number:%d\n",minor);

    /* Get the per-device structure that contains this cdev */
    //sdevp = container_of(inode->i_cdev, struct sdev_dev, cdev);

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


int read_cirq(char *buf, int count, struct cirq *pcq)
{
  int cnt1, cnt2, stat;

  if(pcq->cnt == 0)
    return 0;
  if(count > pcq->cnt)
    count = pcq->cnt;
  if((pcq->rdix + count) <= MAX_BUF_SIZE)
    stat = copy_to_user(buf,&pcq->buf[pcq->rdix],count);
  else
  {
    cnt1 = MAX_BUF_SIZE - pcq->rdix;
    cnt2 = count - cnt1;
    stat = copy_to_user(buf,&pcq->buf[pcq->rdix],cnt1);
    stat = copy_to_user(buf+cnt1,pcq->buf,cnt2);
  }
  pcq->rdix = (pcq->rdix + count) % MAX_BUF_SIZE;
  pcq->cnt  -= count;
  return count;
}


/********* Read from a sample device  *********/
ssize_t sdev_read(struct file *file, char *buf, size_t count, loff_t *ppos)
{
  struct sdev_dev *tdev = file->private_data;

  count = read_cirq(buf,count, &tdev->cque);
	
  printk("<1>" "read called \n");
  return (ssize_t)count;
}


int write_cirq(const char *buf, int count, struct cirq *pcq)
{
  int stat, avl_space, cnt1, cnt2;

  avl_space = MAX_BUF_SIZE - pcq->cnt;
  if(avl_space == 0)
    return 0;
  if(count > avl_space)
    count = avl_space;
  if((pcq->wrix + count) <= MAX_BUF_SIZE)
  {
    stat = copy_from_user(&pcq->buf[pcq->wrix],buf,count);
    printk(KERN_DEBUG "in if pcq->wrix%d count:%d", pcq->wrix,count);
  }
  else
  {
    cnt1 = MAX_BUF_SIZE - pcq->wrix;
    cnt2 = count - cnt1;
    stat = copy_from_user(&pcq->buf[pcq->wrix],buf,cnt1);
    stat = copy_from_user(pcq->buf,buf+cnt1,cnt2);
    printk(KERN_DEBUG "in else pcq->wrix%d count:%d cnt1:%d cnt2:%d", pcq->wrix,count,cnt1,cnt2);
  }
  pcq->wrix = (pcq->wrix + count) % MAX_BUF_SIZE;
  pcq->cnt  += count;
  return count;
}



/********** Write to a sample device ***********/
ssize_t sdev_write(struct file *file, const char *buf, size_t count, 
                                                             loff_t *ppos)
{
  struct sdev_dev *tdev = file->private_data;

  count = write_cirq(buf, count, &tdev->cque);

  printk("<1>" "write called \n");
  return count;
}

module_init(sdev_init);
module_exit(sdev_cleanup); 

MODULE_LICENSE("GPL");

