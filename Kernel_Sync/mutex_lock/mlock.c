// mtx_demo.c
#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/ioctl.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("example");
MODULE_DESCRIPTION("Demo: mutex_lock_interruptible + signal");

#define MTXDEMO_IOC_MAGIC  'M'
/* Hold the mutex for <arg> seconds (simulate long critical section) */
#define MTXDEMO_IOC_HOLD   _IOW(MTXDEMO_IOC_MAGIC, 0x01, unsigned int)

static DEFINE_MUTEX(mtx);

/*
 * .read() tries to take the mutex interruptibly.
 * If someone else is holding it (e.g., via MTXDEMO_IOC_HOLD), this read()
 * will block in mutex_lock_interruptible(). A signal (kill -INT/TSTP/TERM)
 * will interrupt the sleep and return -EINTR to the caller.
 */
static ssize_t mtxdemo_read(struct file *f, char __user *buf,
                            size_t len, loff_t *ppos)
{
    int ret;

    pr_info("mtx_demo: read() trying to take mutex interruptibly...\n");

    mutex_lock(&mtx);
   

    pr_info("mtx_demo: read() acquired mutex; releasing immediately.\n");
    mutex_unlock(&mtx);

    /* Nothing to read; return 0 like EOF */
    return 0;
}

/*
 * IOCTL to simulate a long critical section while holding the mutex.
 * This makes other threads/processes that call read() block on the mutex.
 */
static long mtxdemo_unlocked_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
{
    unsigned int seconds;
    int ret;
    switch (cmd) {
    case MTXDEMO_IOC_HOLD:
        if (copy_from_user(&seconds, (void __user *)arg, sizeof(seconds)))
            return -EFAULT;

        pr_info("mtx_demo: ioctl HOLD for %u seconds; acquiring mutex non-interruptibly.\n", seconds);

        /* The holder takes the mutex with the non-interruptible path to keep it. */
        ret = mutex_lock_interruptible(&mtx);
        if (ret) {
            pr_info("mtx_demo: read() interrupted by signal while waiting for mutex (ret=%d)\n", ret);
            return -ERESTARTSYS; /* common for syscalls so libc may show EINTR */
            }
        while (seconds--) {
            /* Sleep in 1s chunks so removal remains responsive. */
            msleep(1000);
        }

        mutex_unlock(&mtx);
        pr_info("mtx_demo: ioctl HOLD done; mutex released.\n");
        return 0;

    default:
        return -ENOTTY;
    }
}

static const struct file_operations mtxdemo_fops = {
    .owner          = THIS_MODULE,
    .read           = mtxdemo_read,
    .unlocked_ioctl = mtxdemo_unlocked_ioctl,
};

static struct miscdevice mtxdemo_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "mtx_demo",
    .fops  = &mtxdemo_fops,
    .mode  = 0666, /* world-readable for convenience */
};

static int __init mtxdemo_init(void)
{
    int ret = misc_register(&mtxdemo_dev);
    if (ret)
        pr_err("mtx_demo: misc_register failed: %d\n", ret);
    else
        pr_info("mtx_demo: loaded; device /dev/%s\n", mtxdemo_dev.name);
    return ret;
}

static void __exit mtxdemo_exit(void)
{
    misc_deregister(&mtxdemo_dev);
    pr_info("mtx_demo: unloaded\n");
}

module_init(mtxdemo_init);
module_exit(mtxdemo_exit);


