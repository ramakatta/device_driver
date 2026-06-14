#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/capability.h>

#include "ioctl_const.h"

#define CHAR_DEV_NAME "my_cdrv"
#define DEFAULT_LENGTH 4000

/* per-device context */
struct my_device_context {
    char            *device_buf;
    unsigned int     buf_length;
    struct cdev      cdev;
    struct mutex     lock;
};

static struct my_device_context *dev_ctx;
static dev_t mydev;
static struct class *my_class;

/* ---------------- open ---------------- */
static int char_dev_open(struct inode *inode, struct file *file)
{
    static int counter;
    counter++;

    pr_info("%s: open count=%d\n", CHAR_DEV_NAME, counter);
    pr_info("%s: pid=%d\n", CHAR_DEV_NAME, current->pid);

    file->private_data =
        container_of(inode->i_cdev, struct my_device_context, cdev);

    return 0;
}

/* ---------------- release ---------------- */
static int char_dev_release(struct inode *inode, struct file *file)
{
    return 0;
}

/* ---------------- read ---------------- */
static ssize_t char_dev_read(struct file *file, char __user *buf,
                              size_t lbuf, loff_t *ppos)
{
    struct my_device_context *ctx = file->private_data;
    int maxbytes, bytes_to_do, nbytes;

    if (mutex_lock_interruptible(&ctx->lock))
        return -ERESTARTSYS;

    maxbytes = ctx->buf_length - *ppos;

    if (maxbytes <= 0) {
        mutex_unlock(&ctx->lock);
        return 0;
    }

    bytes_to_do = min((size_t)maxbytes, lbuf);

    nbytes = bytes_to_do -
             copy_to_user(buf, ctx->device_buf + *ppos, bytes_to_do);

    if (nbytes == 0 && bytes_to_do > 0) {
        mutex_unlock(&ctx->lock);
        return -EFAULT;
    }

    *ppos += nbytes;

    mutex_unlock(&ctx->lock);
    return nbytes;
}

/* ---------------- write ---------------- */
static ssize_t char_dev_write(struct file *file, const char __user *buf,
                               size_t lbuf, loff_t *ppos)
{
    struct my_device_context *ctx = file->private_data;
    int maxbytes, bytes_to_do, nbytes;

    if (mutex_lock_interruptible(&ctx->lock))
        return -ERESTARTSYS;

    maxbytes = ctx->buf_length - *ppos;

    if (maxbytes <= 0) {
        mutex_unlock(&ctx->lock);
        return -ENOSPC;
    }

    bytes_to_do = min((size_t)maxbytes, lbuf);

    nbytes = bytes_to_do -
             copy_from_user(ctx->device_buf + *ppos, buf, bytes_to_do);

    if (nbytes == 0 && bytes_to_do > 0) {
        mutex_unlock(&ctx->lock);
        return -EFAULT;
    }

    *ppos += nbytes;

    mutex_unlock(&ctx->lock);
    return nbytes;
}

/* ---------------- llseek (NEW) ---------------- */
static loff_t char_dev_llseek(struct file *file, loff_t off, int whence)
{
    struct my_device_context *ctx = file->private_data;

    return fixed_size_llseek(file, off, whence, ctx->buf_length);
}

/* ---------------- ioctl ---------------- */
static long char_dev_ioctl(struct file *filp, unsigned int cmd,
                           unsigned long arg)
{
    struct my_device_context *ctx = filp->private_data;
    unsigned int size, i;
    char *new_buf;
    char c, key;

    if (_IOC_TYPE(cmd) != MY_MAGIC) return -ENOTTY;
    if (_IOC_NR(cmd) > MY_MAX_CMDS) return -ENOTTY;

    switch (cmd) {

    case MY_FILL_ZERO:
        if (mutex_lock_interruptible(&ctx->lock))
            return -ERESTARTSYS;

        memset(ctx->device_buf, 0, ctx->buf_length);

        mutex_unlock(&ctx->lock);
        break;

    case MY_FILL_CHAR:
        if (copy_from_user(&c, (char __user *)arg, 1))
            return -EFAULT;

        if (mutex_lock_interruptible(&ctx->lock))
            return -ERESTARTSYS;

        memset(ctx->device_buf, c, ctx->buf_length);

        mutex_unlock(&ctx->lock);
        break;

    case MY_SET_SIZE:
        if (!capable(CAP_SYS_ADMIN))
            return -EPERM;

        if (copy_from_user(&size, (unsigned int __user *)arg, sizeof(size)))
            return -EFAULT;

        new_buf = kzalloc(size, GFP_KERNEL);
        if (!new_buf)
            return -ENOMEM;

        if (mutex_lock_interruptible(&ctx->lock)) {
            kfree(new_buf);
            return -ERESTARTSYS;
        }

        kfree(ctx->device_buf);
        ctx->device_buf = new_buf;
        ctx->buf_length = size;

        filp->f_pos = 0;

        mutex_unlock(&ctx->lock);
        break;

    case MY_GET_SIZE:
        if (!capable(CAP_SYS_ADMIN))
            return -EPERM;

        size = ctx->buf_length;

        if (copy_to_user((unsigned int __user *)arg, &size, sizeof(size)))
            return -EFAULT;
        break;

    case MY_ENCRYPT:
        if (!capable(CAP_SYS_ADMIN))
            return -EPERM;

        if (copy_from_user(&key, (char __user *)arg, 1))
            return -EFAULT;

        if (mutex_lock_interruptible(&ctx->lock))
            return -ERESTARTSYS;

        for (i = 0; i < ctx->buf_length; i++)
            ctx->device_buf[i] += key;

        mutex_unlock(&ctx->lock);
        break;

    case MY_DECRYPT:
        if (!capable(CAP_SYS_ADMIN))
            return -EPERM;

        if (copy_from_user(&key, (char __user *)arg, 1))
            return -EFAULT;

        if (mutex_lock_interruptible(&ctx->lock))
            return -ERESTARTSYS;

        for (i = 0; i < ctx->buf_length; i++)
            ctx->device_buf[i] -= key;

        mutex_unlock(&ctx->lock);
        break;

    default:
        return -EINVAL;
    }

    return 0;
}

/* ---------------- file ops ---------------- */
static const struct file_operations char_dev_fops = {
    .owner          = THIS_MODULE,
    .open           = char_dev_open,
    .release        = char_dev_release,
    .read           = char_dev_read,
    .write          = char_dev_write,
    .unlocked_ioctl = char_dev_ioctl,
    .llseek         = char_dev_llseek,   /* ✅ ADDED */
};

/* ---------------- init ---------------- */
static int __init char_dev_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&mydev, 0, 1, CHAR_DEV_NAME);
    if (ret < 0)
        return ret;

    dev_ctx = kzalloc(sizeof(*dev_ctx), GFP_KERNEL);
    if (!dev_ctx) goto fail;

    mutex_init(&dev_ctx->lock);

    dev_ctx->device_buf = kzalloc(DEFAULT_LENGTH, GFP_KERNEL);
    if (!dev_ctx->device_buf) goto fail_ctx;

    dev_ctx->buf_length = DEFAULT_LENGTH;

    cdev_init(&dev_ctx->cdev, &char_dev_fops);

    ret = cdev_add(&dev_ctx->cdev, mydev, 1);
    if (ret) goto fail_buf;

    my_class = class_create(CHAR_DEV_NAME);
    if (IS_ERR(my_class)) goto fail_cdev;

    device_create(my_class, NULL, mydev, NULL, "%s", "my_cdrv");

    pr_info("driver loaded\n");
    return 0;

fail_cdev:
    cdev_del(&dev_ctx->cdev);
fail_buf:
    kfree(dev_ctx->device_buf);
fail_ctx:
    kfree(dev_ctx);
fail:
    unregister_chrdev_region(mydev, 1);
    return -ENOMEM;
}

/* ---------------- exit ---------------- */
static void __exit char_dev_exit(void)
{
    device_destroy(my_class, mydev);
    class_destroy(my_class);

    cdev_del(&dev_ctx->cdev);
    unregister_chrdev_region(mydev, 1);

    kfree(dev_ctx->device_buf);
    kfree(dev_ctx);

    pr_info("driver unloaded\n");
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_LICENSE("GPL");
