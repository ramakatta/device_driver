#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/cpuhotplug.h>
#include <linux/kthread.h>
#include <linux/smp.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/delay.h>

#define SIZE 64

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OpenSource");
MODULE_DESCRIPTION("Kernel module using cpuhp_setup_state with misc device and per-CPU threads");

// Define per-CPU thread pointers
static DEFINE_PER_CPU(struct task_struct *, cpu_threads);

// Define a per-CPU data structure
struct my_percpu_data {
    int cpu_id;
    unsigned long counter;
};
static DEFINE_PER_CPU(struct my_percpu_data, cpu_data);

// Global misc device (so we can deregister the same instance)
static struct miscdevice misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "cpu_misc",
    .mode = 0666,
    .fops = NULL,
};

// Hotplug state handle
static int hotplug_state;

// Thread function
static int cpu_thread_fn(void *data)
{
    struct my_percpu_data *pcpu;

    /* This thread will run on a specific CPU because we create it with kthread_create_on_cpu.
       Use this_cpu_ptr here because the thread runs on the CPU the thread was created for. */
    pcpu = this_cpu_ptr(&cpu_data);
    pcpu->cpu_id = smp_processor_id();

    while (!kthread_should_stop()) {
        pcpu->counter++;
        msleep(100);
    }

    return 0;
}

// CPU online callback
static int my_cpu_online(unsigned int cpu)
{
    struct task_struct *t;
    char name[SIZE];

    snprintf(name, SIZE, "cpu_thread/%u", cpu);

    t = kthread_create_on_cpu(cpu_thread_fn, NULL, cpu, name);
    if (IS_ERR(t)) {
        pr_err("Failed to create thread on CPU %u: %ld\n", cpu, PTR_ERR(t));
        return PTR_ERR(t);
    }

    /* store the task pointer for that CPU */
    per_cpu(cpu_threads, cpu) = t;
    wake_up_process(t);
    pr_info("Started thread on CPU %u\n", cpu);
    return 0;
}

// CPU offline callback
static int my_cpu_offline(unsigned int cpu)
{
    struct my_percpu_data *pcpu;
    struct task_struct *t;

    /* Access per-cpu data for the specific cpu using per_cpu() - not this_cpu_ptr(). */
    pcpu = &per_cpu(cpu_data, cpu);
    t = per_cpu(cpu_threads, cpu);

    pr_info("CPU %u: id:%d counter:%lu\n", cpu, pcpu->cpu_id, pcpu->counter);

    if (t) {
        /* Stop the thread and clear stored pointer */
        kthread_stop(t);
        per_cpu(cpu_threads, cpu) = NULL;
    }

    pr_info("Stopped thread on CPU %u\n", cpu);
    return 0;
}

static int __init cpu_misc_init(void)
{
    int ret, cpu;

    /* Register CPU hotplug callbacks */
    ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "misc/cpu_threads:online",
                            my_cpu_online, my_cpu_offline);
    if (ret < 0) {
        pr_err("cpuhp_setup_state failed: %d\n", ret);
        return ret;
    }
    hotplug_state = ret;

    /* Register misc device */
    ret = misc_register(&misc_dev);
    if (ret) {
        pr_err("misc_register failed: %d\n", ret);
        cpuhp_remove_state(hotplug_state);
        return ret;
    }

    /* Start threads for CPUs already online */
    for_each_online_cpu(cpu) {
        /* my_cpu_online will create the thread and set per_cpu pointer */
        ret = my_cpu_online(cpu);
        if (ret)
            pr_warn("failed to start thread on existing online CPU %d: %d\n", cpu, ret);
    }

    pr_info("cpu_misc module loaded\n");
    return 0;
}

static void __exit cpu_misc_exit(void)
{
    int cpu;

    /* Stop per-CPU threads first */
    for_each_possible_cpu(cpu) {
        struct task_struct *t = per_cpu(cpu_threads, cpu);
        if (t) {
            /* Use my_cpu_offline to take care of stopping and clearing pointer and logging */
            my_cpu_offline(cpu);
        }
    }

    /* Remove hotplug state to unregister callbacks */
    cpuhp_remove_state(hotplug_state);

    /* Deregister misc device */
    misc_deregister(&misc_dev);

    pr_info("cpu_misc module unloaded\n");
}

module_init(cpu_misc_init);
module_exit(cpu_misc_exit);

