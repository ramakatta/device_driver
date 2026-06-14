// SPDX-License-Identifier: GPL-2.0

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rama Krishna");
MODULE_DESCRIPTION("IRQ + Tasklet + Workqueue Demo");

#define LOCAL_IRQ_NO 1   /* demo only — NOT recommended in real drivers */

static int my_devid;
static unsigned long isr_cnt;

/* ---------------- Tasklet ---------------- */

static void my_tasklet_handler(struct tasklet_struct *t);

DECLARE_TASKLET(my_tasklet, my_tasklet_handler);

static void my_tasklet_handler(struct tasklet_struct *t)
{
    pr_info("Tasklet running\n");
    pr_info("tasklet: in_interrupt=%d in_irq=%d in_task=%d\n",
            in_interrupt(), in_irq(), in_task());
}

/* ---------------- Workqueue ---------------- */

static void my_work_handler(struct work_struct *work);

static DECLARE_WORK(my_work, my_work_handler);

static void my_work_handler(struct work_struct *work)
{
    pr_info("Workqueue running\n");
    pr_info("work: in_interrupt=%d in_irq=%d in_task=%d\n",
            in_interrupt(), in_irq(), in_task());
}

/* ---------------- Interrupt Handler ---------------- */

static irqreturn_t isr_routine(int irq, void *dev_id)
{
    isr_cnt++;

    pr_info("ISR triggered (count=%lu)\n", isr_cnt);
    pr_info("ISR: in_interrupt=%d in_irq=%d in_task=%d\n",
            in_interrupt(), in_irq(), in_task());

    /* defer work */
    tasklet_schedule(&my_tasklet);
    schedule_work(&my_work);

    return IRQ_HANDLED;
}

/* ---------------- Init ---------------- */

static int __init irq_demo_init(void)
{
    int ret;

    ret = request_irq(LOCAL_IRQ_NO,
                      isr_routine,
                      IRQF_SHARED,
                      "irq_demo",
                      &my_devid);

    if (ret) {
        pr_err("Failed to request IRQ %d (err=%d)\n",
               LOCAL_IRQ_NO, ret);
        return ret;
    }

    pr_info("IRQ module loaded on IRQ %d\n", LOCAL_IRQ_NO);
    return 0;
}

/* ---------------- Cleanup ---------------- */

static void __exit irq_demo_exit(void)
{
    free_irq(LOCAL_IRQ_NO, &my_devid);

    tasklet_kill(&my_tasklet);
    cancel_work_sync(&my_work);

    pr_info("IRQ module unloaded cleanly\n");
}

module_init(irq_demo_init);
module_exit(irq_demo_exit);
