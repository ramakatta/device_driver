#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/sched.h>

static struct task_struct *even_thread;
static struct task_struct *odd_thread;

static wait_queue_head_t wq;
static int flag = 0;  // 0 = even's turn, 1 = odd's turn
static int done = 0;     // stop condition

#define MAX_NUM 20

static int even_fn(void *data)
{
    int i = 0;
    while (i < MAX_NUM) {
        wait_event_interruptible(wq, (flag == 0 || kthread_should_stop()));
        if (kthread_should_stop())
            break;
        if (i % 2 == 0) {
            printk(KERN_INFO "Even: %d\n", i);
            i += 2;
            flag = 1;
            wake_up_interruptible(&wq);
        }
    }
    return 0;
}

static int odd_fn(void *data)
{
    int i = 1;
    while (i < MAX_NUM) {
        wait_event_interruptible(wq, (flag == 1 || kthread_should_stop()));
        if (kthread_should_stop())
            break;
        if (i % 2 == 1) {
            printk(KERN_INFO "Odd: %d\n", i);
            i += 2;
            flag = 0;
            wake_up_interruptible(&wq);
        }
    }
    return 0;
}

static int __init thread_init(void)
{
    printk(KERN_INFO "Loading even/odd synchronized kernel threads...\n");
    init_waitqueue_head(&wq);

    even_thread = kthread_run(even_fn, NULL, "even_thread");
    if (IS_ERR(even_thread)) {
        printk(KERN_ERR "Failed to create even thread\n");
        return PTR_ERR(even_thread);
    }

    odd_thread = kthread_run(odd_fn, NULL, "odd_thread");
    if (IS_ERR(odd_thread)) {
        printk(KERN_ERR "Failed to create odd thread\n");
        kthread_stop(even_thread);
        return PTR_ERR(odd_thread);
    }

    return 0;
}

static void __exit thread_exit(void)
{
    printk(KERN_INFO "Stopping threads...\n");
    if (even_thread)
        kthread_stop(even_thread);
    if (odd_thread)
        kthread_stop(odd_thread);
    wake_up_interruptible(&wq);  // in case threads are sleeping
}

module_init(thread_init);
module_exit(thread_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Open source");
MODULE_DESCRIPTION("Synchronized Even/Odd Kernel Threads");

