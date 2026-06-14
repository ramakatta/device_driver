#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>

MODULE_AUTHOR("Rama Krishna");
MODULE_LICENSE("GPL");

#define LOCAL_IRQ_NO 1

static int dev_id;

/* ================= Hard IRQ ================= */
static irqreturn_t isr_top_half(int irq, void *dev_id)
{
    pr_info("=== Hard IRQ (top half) ===\n");
    pr_info("in_interrupt: %d\n", in_interrupt());
    pr_info("in_irq: %d\n", in_irq());
    pr_info("in_task: %d\n", in_task());

    return IRQ_WAKE_THREAD;
}

/* ================= Threaded IRQ ================= */
static irqreturn_t isr_bottom_half(int irq, void *dev_id)
{
    pr_info("=== Threaded IRQ (bottom half) ===\n");
    pr_info("in_interrupt: %d\n", in_interrupt());
    pr_info("in_irq: %d\n", in_irq());
    pr_info("in_task: %d\n", in_task());

    return IRQ_HANDLED;
}

/* ================= Init ================= */
static int __init irq_demo_init(void)
{
    int ret;

    ret = request_threaded_irq(
        LOCAL_IRQ_NO,
        isr_top_half,
        isr_bottom_half,
        IRQF_SHARED,
        "irq_demo",
        &dev_id
    );

    if (ret) {
        pr_err("Failed to request IRQ %d (err=%d)\n", LOCAL_IRQ_NO, ret);
        return ret;
    }

    pr_info("IRQ %d registered successfully\n", LOCAL_IRQ_NO);
    return 0;
}

/* ================= Exit ================= */
static void __exit irq_demo_exit(void)
{
    free_irq(LOCAL_IRQ_NO, &dev_id);
    pr_info("IRQ %d freed successfully\n", LOCAL_IRQ_NO);
}

module_init(irq_demo_init);
module_exit(irq_demo_exit);
