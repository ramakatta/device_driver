#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>

static struct hrtimer my_timer;
static struct work_struct sample_work;
static spinlock_t data_lock;

static unsigned long sample_value;
static ktime_t interval;

/* --- Workqueue handler --- */
static void sample_work_func(struct work_struct *work)
{
    unsigned long irq_flags;
    unsigned long local_copy;

    /* Safely read the shared data */
    spin_lock_irqsave(&data_lock, irq_flags);
    local_copy = sample_value;
    spin_unlock_irqrestore(&data_lock, irq_flags);

    pr_info("Workqueue processed sample value: %lu\n", local_copy);
}

/* --- Timer callback --- */
static enum hrtimer_restart my_timer_callback(struct hrtimer *timer)
{
    unsigned long irq_flags;

    /* Protect shared resource */
    spin_lock_irqsave(&data_lock, irq_flags);
    sample_value++;
    spin_unlock_irqrestore(&data_lock, irq_flags);

    /* Queue work to process data in process context */
    schedule_work(&sample_work);

    /* Restart periodic timer */
    hrtimer_forward_now(timer, interval);
    return HRTIMER_RESTART;
}

/* --- Module initialization --- */
static int __init my_module_init(void)
{
    pr_info("==> hrtimer + spinlock + workqueue example loaded\n");

    spin_lock_init(&data_lock);
    INIT_WORK(&sample_work, sample_work_func);
    sample_value = 0;

    /* 100 ms timer period */
    interval = ktime_set(0, 100 * 1000000);

    /* Setup high-resolution timer */
    hrtimer_setup(&my_timer, my_timer_callback, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

    hrtimer_start(&my_timer, interval, HRTIMER_MODE_REL);
    return 0;
}

/* --- Module cleanup --- */
static void __exit my_module_exit(void)
{
    pr_info("==> unloading module\n");

    /* 1. Cancel timer and wait for any running callback */
    hrtimer_cancel(&my_timer);

    /* 2. Cancel any pending work safely */
    cancel_work_sync(&sample_work);

    /* 3. Safe read of shared data (no more writers now) */
    pr_info("Final sample value: %lu\n", sample_value);
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Open source");
MODULE_DESCRIPTION("High-resolution timer with spinlock and workqueue synchronization");

