#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/refcount.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Open Source");
MODULE_DESCRIPTION("refcount_t Example in Kernel Module");

struct my_object {
    refcount_t refcount;
    int data;
};

static struct my_object *obj;

static struct task_struct *incref_thread;
static struct task_struct *decref_thread;

static int incref_fn(void *data)
{
    int i;
    for (i = 0; i < 5; i++) {
        ssleep(1);
        refcount_inc(&obj->refcount);
        printk(KERN_INFO "Incref: refcount = %d\n", refcount_read(&obj->refcount));
    }
    return 0;
}

static int decref_fn(void *data)
{
    int i;
    for (i = 0; i < 6; i++) {
        ssleep(2);
        if (refcount_dec_and_test(&obj->refcount)) {
            printk(KERN_INFO "Decref: refcount = 0, cleaning up object\n");
            kfree(obj);
            obj = NULL;
            break;
        } else {
            printk(KERN_INFO "Decref: refcount = %d\n", refcount_read(&obj->refcount));
        }
    }
    return 0;
}

static int __init refcount_example_init(void)
{
    printk(KERN_INFO "Loading refcount_t example...\n");

    obj = kmalloc(sizeof(*obj), GFP_KERNEL);
    if (!obj)
        return -ENOMEM;

    obj->data = 123;
    refcount_set(&obj->refcount, 1);  // Initial reference

    incref_thread = kthread_run(incref_fn, NULL, "incref_thread");
    decref_thread = kthread_run(decref_fn, NULL, "decref_thread");

    return 0;
}

static void __exit refcount_example_exit(void)
{
    printk(KERN_INFO "Unloading module...\n");
    if (incref_thread)
        kthread_stop(incref_thread);
    if (decref_thread)
        kthread_stop(decref_thread);
    if (obj) {
        printk(KERN_INFO "Forcing cleanup (refcount leak detected!)\n");
        kfree(obj);
    }
}

module_init(refcount_example_init);
module_exit(refcount_example_exit);

