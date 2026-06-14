#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/compiler.h>

#define MAX_NUM 20

static struct task_struct *even_thread;
static struct task_struct *odd_thread;

static wait_queue_head_t wq;

/* 0 = even thread's turn, 1 = odd thread's turn */
static int flag = 0;

/*------------------------------------------------------------------*/
/* Even Thread                                                      */
/*------------------------------------------------------------------*/
static int even_fn(void *data)
{
    int i = 0;
    int ret;

    while (!kthread_should_stop() && i < MAX_NUM) {

        ret = wait_event_interruptible(
                wq,
                READ_ONCE(flag) == 0 || kthread_should_stop());

        if (kthread_should_stop())
            break;

        if (ret)
            continue;   /* interrupted by signal */

        pr_info("Even: %d\n", i);

        i += 2;

        WRITE_ONCE(flag, 1);

        wake_up_interruptible(&wq);
    }

    pr_info("Even thread exiting\n");
    return 0;
}

/*------------------------------------------------------------------*/
/* Odd Thread                                                       */
/*------------------------------------------------------------------*/
static int odd_fn(void *data)
{
    int i = 1;
    int ret;

    while (!kthread_should_stop() && i < MAX_NUM) {

        ret = wait_event_interruptible(
                wq,
                READ_ONCE(flag) == 1 || kthread_should_stop());

        if (kthread_should_stop())
            break;

        if (ret)
            continue;

        pr_info("Odd : %d\n", i);

        i += 2;

        WRITE_ONCE(flag, 0);

        wake_up_interruptible(&wq);
    }

    pr_info("Odd thread exiting\n");
    return 0;
}

/*------------------------------------------------------------------*/
/* Module Init                                                      */
/*------------------------------------------------------------------*/
static int __init thread_init(void)
{
    pr_info("Loading synchronized kernel threads...\n");

    init_waitqueue_head(&wq);

    even_thread = kthread_run(even_fn, NULL, "even_thread");
    if (IS_ERR(even_thread)) {
        pr_err("Failed to create even thread\n");
        return PTR_ERR(even_thread);
    }

    odd_thread = kthread_run(odd_fn, NULL, "odd_thread");
    if (IS_ERR(odd_thread)) {
        pr_err("Failed to create odd thread\n");

        /*
         * Wake the even thread (if sleeping), then stop it.
         */
        wake_up_interruptible(&wq);
        kthread_stop(even_thread);

        return PTR_ERR(odd_thread);
    }

    return 0;
}

/*------------------------------------------------------------------*/
/* Module Exit                                                      */
/*------------------------------------------------------------------*/
static void __exit thread_exit(void)
{
    pr_info("Stopping threads...\n");

    /*
     * Wake sleeping threads so they can observe
     * kthread_should_stop().
     */
    wake_up_interruptible(&wq);

    if (even_thread)
        kthread_stop(even_thread);

    if (odd_thread)
        kthread_stop(odd_thread);

    pr_info("Module unloaded\n");
}

module_init(thread_init);
module_exit(thread_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Open Source");
MODULE_DESCRIPTION("Synchronized Even/Odd Kernel Threads using Wait Queue");