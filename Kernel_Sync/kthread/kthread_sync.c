#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h> 
#include <linux/errno.h>  
#include <linux/types.h> 
#include <linux/mutex.h> 
#include <linux/completion.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/atomic.h>
#include <linux/semaphore.h>


int kthread1(void *data);
int kthread2(void *data);

struct task_struct *task1;
struct task_struct *task2;

int thread1_status;
int thread2_status;

DECLARE_WAIT_QUEUE_HEAD(thread1_wait_queue);
DECLARE_WAIT_QUEUE_HEAD(thread2_wait_queue);

//struct semaphore thread_sem;
struct mutex thread_lock;

// Atomic variable used as flag to control the start of the threads 
atomic_t first_flag;

// Global variable which is protected by Mutex
int count=1;

/*
 * kmod1_init :
 * 		The init function (probe).
 * 		it is invoked by register_netdev()
 */
int kmod1_init(void)
{
	printk(KERN_INFO "kthread_sync module initialize \n");

	// Reset atomic variable first_flag to zero
	atomic_set(&first_flag, 0);
	
	// Initialize Mutex thread_lock
	mutex_init(&thread_lock);
	
	printk("Starting Kthread1 \n");
	// Create and run kthread1
	task1 = kthread_run(kthread1, NULL,"Thread1");

	printk("Starting Kthread2 \n");
	// Create and run kthread2
	task2 = kthread_run(kthread2, NULL,"Thread2");

	printk(KERN_INFO "kthread_sync module initialized \n");
	return 0;
}

// Display Odd Number Only
int kthread1(void *data)
{
	// increment atomic variable so that thread2 can also be scheduled
	atomic_inc(&first_flag);
	
	while(count <= 50)
	{
		
		// acquire mutex lock
		mutex_lock(&thread_lock);
		printk("%s: print number is %d \n", __FUNCTION__,  count);
		// increment count
		count++;

		// unlock mutex
		mutex_unlock(&thread_lock);

		// sleep for 10 ms to allow other thread to run using msleep()
		msleep(10);	
	}		

	// Wait on a queue event to allow this thread to sleep
	wait_event_interruptible(thread1_wait_queue, thread1_status);
	
	// Kernel thread woke up and exiting
	printk("Kthread1 exiting \n");

	return 0;
}

// Display Even Number Only
int kthread2(void *data)
{
	// Wait for Thread 1 to execute first.
	while( atomic_read(&first_flag) == 0);

	while(count <= 50)
	{


		// acquire mutex lock
		mutex_lock(&thread_lock);
		printk("%s: print number is %d \n", __FUNCTION__,  count);
		// increment count
		count++;

		// unlock mutex
		mutex_unlock(&thread_lock);

		// sleep for 10 ms to allow other thread to run using msleep()
		msleep(10);	
	}

	// Wait on a queue event to allow this thread to sleep
	wait_event_interruptible(thread2_wait_queue, thread2_status);

	// Kernel thread woke up and exiting
	printk("Kthread2 exiting \n");
	return 0;
}

/*
 * kmod1_cleanup :
 *		Driver Exit Cleanup Routine
 *		this function is called just before the driver is removed
 *		from memory.
 */
void kmod1_cleanup(void)
{
	printk(KERN_INFO "kthread_sync module cleanup... \n");

	printk(KERN_INFO "Wake up threads...so they exits.\n");

	thread1_status=1;
	// Wake up thread1
	wake_up_interruptible(&thread1_wait_queue);

	thread2_status=1;
	// Wake up thread2
	wake_up_interruptible(&thread2_wait_queue);
	
	// Sleep for some milliseconds to allow threads to exit
	msleep(10);

	printk(KERN_INFO "kthread_sync module cleaned up \n");
	return ;
}

module_init(kmod1_init);
module_exit(kmod1_cleanup);
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

