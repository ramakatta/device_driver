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

// Thread function
static int cpu_thread_fn(void *data) {
    struct my_percpu_data *pcpu = this_cpu_ptr(&cpu_data);
    pcpu->cpu_id = smp_processor_id();

    while (!kthread_should_stop()) {
        pcpu->counter++;
        msleep(100);
    }

    return 0;
}

// CPU online callback
static int my_cpu_online(unsigned int cpu) {
    struct task_struct *t;
    char buffer[SIZE];
    snprintf(buffer,SIZE,"%s%d", "cpu_thread/",cpu);

    t = kthread_create_on_cpu(cpu_thread_fn, NULL, cpu, buffer);
    if (IS_ERR(t))
        return PTR_ERR(t);

    per_cpu(cpu_threads, cpu) = t;
    wake_up_process(t);
    pr_info("Started thread on CPU %u\n", cpu);
    return 0;
}

// CPU offline callback
static int my_cpu_offline(unsigned int cpu) {
    struct task_struct *t = per_cpu(cpu_threads, cpu);
    if (t)
        kthread_stop(t);
    pr_info("Stopped thread on CPU %u\n", cpu);
    return 0;
}

// Hotplug state handle
static int hotplug_state;

static int __init cpu_misc_init(void) {
    int ret;

    // Register CPU hotplug callbacks
    ret = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "misc/cpu_threads:online",
                            my_cpu_online, my_cpu_offline);
    if (ret < 0)
        return ret;

    hotplug_state = ret;

    // Register misc device
    static struct miscdevice misc_dev = {
        .minor = MISC_DYNAMIC_MINOR,
        .name = "cpu_misc",
        .mode = 0666,
        .fops = NULL,
    };

    ret = misc_register(&misc_dev);
    if (ret)
        cpuhp_remove_state(hotplug_state);

    pr_info("cpu_misc module loaded\n");
    return ret;
}

static void __exit cpu_misc_exit(void) {
    int cpu;

    cpuhp_remove_state(hotplug_state);

    // Stop per-CPU threads
    for_each_online_cpu(cpu) {
        my_cpu_offline(cpu);
    }

    misc_deregister(&(struct miscdevice){ .name = "cpu_misc" });

    pr_info("cpu_misc module unloaded\n");
}

module_init(cpu_misc_init);
module_exit(cpu_misc_exit);

