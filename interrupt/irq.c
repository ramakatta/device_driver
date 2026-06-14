// SPDX-License-Identifier: GPL-2.0

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#define LOCAL_IRQ_NO   1

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rama Krishna");
MODULE_DESCRIPTION("Simple Interrupt Handler Example");

static unsigned long isr_count;
static int irq_dev_id;

/*
 * Interrupt Service Routine
 */
static irqreturn_t isr_routine(int irq, void *dev_id)
{
    /*
     * NOTE:
     * Since this example uses IRQF_SHARED but does not own any hardware,
     * it cannot determine whether this interrupt belongs to it.
     *
     * A real driver should check the device's interrupt status register:
     *
     *      if (!device_generated_interrupt())
     *              return IRQ_NONE;
     */

    isr_count++;

    pr_info("Interrupt %d received (count = %lu)\n",
            irq, isr_count);

    pr_info("in_interrupt=%d in_irq=%d in_task=%d\n",
             in_interrupt(),
             in_irq(),
             in_task());

    return IRQ_HANDLED;
}

int my_driver_setup_irq(unsigned int irq)
{
    // static ensures the memory persists after this function returns
    static struct cpumask static_cpu_mask;
    int ret;

    // 1. Clear any existing bits in the mask
    cpumask_clear(&static_cpu_mask);

    // 2. Explicitly set CPU 2 and CPU 4
    cpumask_set_cpu(2, &static_cpu_mask);
    cpumask_set_cpu(4, &static_cpu_mask);

    // 3. Apply the hint and hardware routing safely
    ret = irq_set_affinity_and_hint(irq, &static_cpu_mask);
    if (ret) {
        pr_err("Failed to set IRQ affinity for CPU 2,4: %d\n", ret);
        return ret;
    }

    return 0;
}

static int __init irq_example_init(void)
{
    int ret;

    ret = request_irq(LOCAL_IRQ_NO,
                      isr_routine,
                      IRQF_SHARED,
                      "irq_example",
                      &irq_dev_id);
    if (ret) {
        pr_err("Failed to register IRQ %d (error %d)\n",
               LOCAL_IRQ_NO, ret);
        return ret;
    }
    my_driver_setup_irq(LOCAL_IRQ_NO);
    pr_info("IRQ %d registered successfully\n", LOCAL_IRQ_NO);

    return 0;
}

static void __exit irq_example_exit(void)
{
    irq_set_affinity_and_hint(LOCAL_IRQ_NO, NULL);
    free_irq(LOCAL_IRQ_NO, &irq_dev_id);

    pr_info("IRQ handler unloaded\n");
}

module_init(irq_example_init);
module_exit(irq_example_exit);
