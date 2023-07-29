// Simple Character Device Driver Module for Raspberry Pi.
/*
 * DESCRIPTION:
 *     a simple example of char device 
 *     this char device can control the GPIO by file operation : write
 *     to write specific message as command
 * */

#include <linux/module.h>   
#include <linux/string.h>    
#include <linux/fs.h>      
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/cdev.h>

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include <linux/list.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>


#define RED_LED 20
#define YELLOW_LED 10
#define BLUE_LED 9
#define NUM_GPIO_LED 3

/* Per-device structure */
struct rgb_led 
{
  int  index;
  char   name[16];
  struct cdev cdev;               /* The cdev structure */
  char msg;  /* buffer to hold led value */

} *rgb_ledp;

struct rgb_led *rgb_ledps[NUM_GPIO_LED];

struct class *myclass;

int gpio_array[NUM_GPIO_LED] = {RED_LED, YELLOW_LED, BLUE_LED};

#define DEVICE_NAME  "RGB_led"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rama");
MODULE_DESCRIPTION("A Simple GPIO Device Driver module for RaspPi");

static int     my_open( struct inode *, struct file * );
static ssize_t my_read( struct file * ,        char *  , size_t, loff_t *);
static ssize_t my_write(struct file * , const  char *  , size_t, loff_t *);
static int     my_close(struct inode *, struct file * );

struct file_operations my_fops = {
        read    :       my_read,
        write   :       my_write,
        open    :       my_open,
        release :       my_close,
        owner   :       THIS_MODULE
};


/* Device number contain major and minor */
dev_t devno;

/*
 * INIT_MODULE -- MODULE START --
 * */

int init_module(void)
{

	int i, ret;
	/* Request dynamic allocation of a device major number */
        if (alloc_chrdev_region(&devno, 0,
                        NUM_GPIO_LED, DEVICE_NAME) < 0)
        {
             pr_info("Can't register device\n");
             return -1;
        }

  	printk("Major : %u\n", MAJOR(devno));
  	printk("Minor : %u\n", MINOR(devno));

        myclass = class_create(THIS_MODULE, DEVICE_NAME);

        for (i=0; i<NUM_GPIO_LED; i++)
        {
         /* Allocate memory for the per-device structure */
         rgb_ledp = kmalloc(sizeof(struct rgb_led), GFP_KERNEL);
         if (!rgb_ledp)
         {
            printk("Bad Kmalloc\n"); return -ENOMEM;
         }
	 sprintf(rgb_ledp->name, "led%d",i);
	 rgb_ledp->index = i;

         /* Connect the file operations with the cdev */
         cdev_init(&rgb_ledp->cdev, &my_fops);
         rgb_ledp->cdev.owner = THIS_MODULE;

         /* Connect the major/minor number to the cdev */
         ret = cdev_add(&rgb_ledp->cdev, (devno + i), 1);
         if (ret)
         {
             printk("Bad cdev\n");
             return ret;
         }
         device_create(myclass, NULL, (devno + i), NULL, "led%d", i);
         rgb_ledps[i] = rgb_ledp;
        

	 if(gpio_is_valid(gpio_array[i]) < 0){
		pr_info("gpio %d is valid error \n", gpio_array[i]);
		return -1;
	 }
	 if(gpio_request(gpio_array[i],"LED_GPIO") < 0){
		pr_info("gpio %d is request error \n", gpio_array[i]);
		return -1;
	 }
	 gpio_direction_output(gpio_array[i], 0);
         /* Using this call the GPIO 21 will be visible in /sys/class/gpio/
 	  ** Now you can change the gpio values by using below commands also.
	  ** echo 1 > /sys/class/gpio/gpio21/value  (turn ON the LED)
	  ** echo 0 > /sys/class/gpio/gpio21/value  (turn OFF the LED)
  	  ** cat /sys/class/gpio/gpio21/value  (read the value LED)
  	  ** 
  	  ** the second argument prevents the direction from being changed.
  	*/
  	gpio_export(gpio_array[i], false);

       }
        return 0;
}



/*
 * CLEANUP_MODULE -- MODULE END --
 * */
void cleanup_module(void)
{
	int i;
        pr_info("<1> Goodbye\n");

	/* Release the major number */
        unregister_chrdev_region((devno), NUM_GPIO_LED);

        for (i=0; i<NUM_GPIO_LED; i++)
        {
          device_destroy(myclass, devno + i);
          cdev_del(&rgb_ledps[i]->cdev);
          kfree(rgb_ledps[i]);
	  gpio_set_value(gpio_array[i],0);
	  gpio_free(gpio_array[i]);
        }
        class_destroy(myclass);

}


/*
 * file operation: OPEN 
 * */
static int my_open(struct inode *inode, struct file *file)
{
	 struct rgb_led *ledp;

        /* Get the per-device structure that contains this cdev */
        ledp = container_of(inode->i_cdev, struct rgb_led, cdev);

        /* Easy access to sdev_devp from rest of the entry points */
        file->private_data = ledp;

    return 0;
}




/*
 * file operation: READ
 * */
static ssize_t my_read(struct file *filp, char *buff, size_t len, loff_t *off)
{
	int  count;
	struct rgb_led *ledp = filp->private_data;;

	ledp->msg = gpio_get_value(gpio_array[ledp->index]);
	len = 1;

	count = copy_to_user(buff, &ledp->msg, len);
	pr_info("GPIO%d=%d \n",gpio_array[ledp->index],gpio_get_value(gpio_array[ledp->index]));

	return 0;
}


/*
 * file operation: WRITE
 * */
static ssize_t my_write(struct file *filp, const char *buff, size_t len, loff_t *off)
{
	struct rgb_led *ledp = filp->private_data;;
	int count;

	count = copy_from_user( &ledp->msg, buff, len );

	if (ledp->msg == 1) {
		gpio_set_value(gpio_array[ledp->index], 1);     // LED 0 ON
	} else if (ledp->msg == 0) {
		gpio_set_value(gpio_array[ledp->index], 0);     // LED 0 OFF
	}  else 
		pr_info("Unknown command , 1 or 0 \n");

	return len;
}



/*
 * file operation : CLOSE
 * */
static int my_close(struct inode *inod, struct file *fil)
{
	int minor;

	minor = MINOR(fil->f_path.dentry->d_inode->i_rdev);
	pr_info("*****Some body is closing me at major %d*****\n",minor);

	return 0;
}
