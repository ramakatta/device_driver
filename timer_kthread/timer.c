#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OpenSource");
MODULE_DESCRIPTION("Kernel module using timer and kernel thread");

static struct task_struct *my_thread;

static struct timer_list my_timer;

static int timer_period_ms = 1000; // 1 second
static bool timer_flag = false;
static DEFINE_SPINLOCK(flag_lock);  // protect access to timer_flag

// Timer callback function
static void timer_callback(struct timer_list *t)
{
    unsigned long flags;

    pr_info("Timer continuting....\n");
    spin_lock_irqsave(&flag_lock, flags);
    timer_flag = true;
    spin_unlock_irqrestore(&flag_lock, flags);

    // Restart the timer
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(timer_period_ms));
}

// Kernel thread function
static int my_thread_fn(void *data)
{
    pr_info("Timer thread started\n");

    while (!kthread_should_stop()) {
        bool local_flag = false;
        unsigned long flags;

        // Check the flag set by the timer
        spin_lock_irqsave(&flag_lock, flags);
        if (timer_flag) {
            local_flag = true;
            timer_flag = false;
        }
        spin_unlock_irqrestore(&flag_lock, flags);

        if (local_flag) {
            pr_info("Thread triggered by timer at jiffies=%lu\n", jiffies);
        }

        msleep(100); // Sleep to reduce CPU usage
    }

    pr_info("Timer thread exiting\n");
    return 0;
}

static int __init timer_thread_init(void)
{
    pr_info("Initializing timer thread module\n");

    // Setup and start timer
    timer_setup(&my_timer, timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(timer_period_ms));

    // Start kernel thread
    my_thread = kthread_run(my_thread_fn, NULL, "my_timer_thread");
    if (IS_ERR(my_thread)) {
        del_timer_sync(&my_timer);
        pr_err("Failed to create thread\n");
        return PTR_ERR(my_thread);
    }

    return 0;
}

static void __exit timer_thread_exit(void)
{
    pr_info("Exiting timer thread module\n");

    // Stop the timer
    del_timer_sync(&my_timer);

    // Stop the thread
    if (my_thread)
        kthread_stop(my_thread);
}

module_init(timer_thread_init);
module_exit(timer_thread_exit);

