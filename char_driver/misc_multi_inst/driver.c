#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Open source");
MODULE_DESCRIPTION("Multi-instance misc device driver");
MODULE_VERSION("1.0");

#define MAX_INSTANCES 4
#define BUFFER_SIZE 256

struct my_device_instance {
    struct miscdevice misc;
    char buffer[BUFFER_SIZE];
    size_t data_len;
    struct mutex lock;
    int instance_id;
};

static struct my_device_instance *devices[MAX_INSTANCES];

/* -------- open -------- */
static int my_open(struct inode *inode, struct file *file)
{
    struct miscdevice *m = file->private_data;
    struct my_device_instance *inst =
        container_of(m, struct my_device_instance, misc);

    file->private_data = inst;

    pr_info("multi_misc: opened instance %d\n", inst->instance_id);
    return 0;
}

/* -------- release -------- */
static int my_release(struct inode *inode, struct file *file)
{
    struct my_device_instance *inst = file->private_data;

    pr_info("multi_misc: closed instance %d\n", inst->instance_id);
    return 0;
}

/* -------- read -------- */
static ssize_t my_read(struct file *file, char __user *buf,
                       size_t count, loff_t *ppos)
{
    struct my_device_instance *inst = file->private_data;

    if (mutex_lock_interruptible(&inst->lock))
        return -ERESTARTSYS;

    if (*ppos >= inst->data_len) {
        mutex_unlock(&inst->lock);
        return 0;
    }

    if (count > inst->data_len - *ppos)
        count = inst->data_len - *ppos;

    if (copy_to_user(buf, inst->buffer + *ppos, count)) {
        mutex_unlock(&inst->lock);
        return -EFAULT;
    }

    *ppos += count;

    mutex_unlock(&inst->lock);
    return count;
}

/* -------- write -------- */
static ssize_t my_write(struct file *file, const char __user *buf,
                        size_t count, loff_t *ppos)
{
    struct my_device_instance *inst = file->private_data;

    if (mutex_lock_interruptible(&inst->lock))
        return -ERESTARTSYS;

    if (count > BUFFER_SIZE)
        count = BUFFER_SIZE;

    if (copy_from_user(inst->buffer, buf, count)) {
        mutex_unlock(&inst->lock);
        return -EFAULT;
    }

    inst->data_len = count;
    *ppos = 0;

    mutex_unlock(&inst->lock);

    pr_info("multi_misc: wrote %zu bytes to instance %d\n",
            count, inst->instance_id);

    return count;
}

/* -------- fops -------- */
static const struct file_operations my_fops = {
    .owner   = THIS_MODULE,
    .open    = my_open,
    .release = my_release,
    .read    = my_read,
    .write   = my_write,
};

/* -------- init -------- */
static int __init multi_misc_init(void)
{
    int i, ret;

    pr_info("multi_misc: init\n");

    for (i = 0; i < MAX_INSTANCES; i++) {

        devices[i] = kzalloc(sizeof(*devices[i]), GFP_KERNEL);
        if (!devices[i]) {
            ret = -ENOMEM;
            goto err;
        }

        devices[i]->instance_id = i;
        mutex_init(&devices[i]->lock);

        devices[i]->misc.minor = MISC_DYNAMIC_MINOR;
        devices[i]->misc.fops  = &my_fops;

        devices[i]->misc.name =
            kasprintf(GFP_KERNEL, "multi_misc%d", i);

        if (!devices[i]->misc.name) {
            kfree(devices[i]);
            devices[i] = NULL;
            ret = -ENOMEM;
            goto err;
        }

        ret = misc_register(&devices[i]->misc);
        if (ret) {
            kfree(devices[i]->misc.name);
            kfree(devices[i]);
            devices[i] = NULL;
            goto err;
        }

        pr_info("multi_misc: registered /dev/multi_misc%d\n", i);
    }

    return 0;

err:
    while (--i >= 0) {
        if (devices[i]) {
            misc_deregister(&devices[i]->misc);
            kfree(devices[i]->misc.name);
            kfree(devices[i]);
        }
    }
    return ret;
}

/* -------- exit -------- */
static void __exit multi_misc_exit(void)
{
    int i;

    pr_info("multi_misc: exit\n");

    for (i = 0; i < MAX_INSTANCES; i++) {
        if (devices[i]) {
            misc_deregister(&devices[i]->misc);
            kfree(devices[i]->misc.name);
            kfree(devices[i]);
        }
    }
}

module_init(multi_misc_init);
module_exit(multi_misc_exit);
