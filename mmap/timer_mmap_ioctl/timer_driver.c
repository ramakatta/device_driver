/*
 * Raspberry Pi System Timer Character Device Driver
 *
 * Provides:
 *   - open()
 *   - release()
 *   - read()
 *   - write()
 *   - ioctl()
 *   - mmap()
 *
 * Device:
 *   /dev/timer_mmap
 *
 * Header:
 *   timer_ioctl.h
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/types.h>

#include "timer_ioctl.h"


/* ============================================================
 * Device configuration
 * ============================================================
 */

/*
 * Raspberry Pi 4 peripheral base:
 *
 *     0xFE000000
 *
 * System Timer:
 *
 *     0xFE003000
 *
 * NOTE:
 * Verify the peripheral address for your specific Raspberry Pi
 * and kernel/device-tree configuration.
 */
#define TIMER_BASE_ADDR     0xFE003000
#define TIMER_SIZE          0x1000

#define DEVICE_NAME         "timer_mmap"


/* ============================================================
 * Character device variables
 * ============================================================
 */

static dev_t dev_num;
static struct cdev timer_cdev;
static struct class *timer_class;

/*
 * Kernel virtual address of the timer registers.
 */
static void __iomem *timer_base;


/* ============================================================
 * Register validation
 * ============================================================
 */

static bool timer_valid_register(u32 reg)
{
    switch (reg) {

    case TIMER_CS:
    case TIMER_CLO:
    case TIMER_CHI:
    case TIMER_C0:
    case TIMER_C1:
    case TIMER_C2:
    case TIMER_C3:
        return true;

    default:
        return false;
    }
}


/* ============================================================
 * Open
 * ============================================================
 */

static int timer_open(struct inode *inode, struct file *filp)
{
    pr_info("timer_mmap: device opened\n");

    return 0;
}


/* ============================================================
 * Release
 * ============================================================
 */

static int timer_release(struct inode *inode, struct file *filp)
{
    pr_info("timer_mmap: device released\n");

    return 0;
}


/* ============================================================
 * READ
 *
 * Register offset is supplied through file position.
 *
 * Example from user space:
 *
 *     lseek(fd, TIMER_CLO, SEEK_SET);
 *     read(fd, &value, sizeof(value));
 *
 * ============================================================
 */

static ssize_t timer_read(struct file *filp,
                          char __user *buf,
                          size_t count,
                          loff_t *ppos)
{
    u32 reg;
    u32 value;

    /*
     * Only 32-bit register accesses are supported.
     */
    if (count != sizeof(u32))
        return -EINVAL;

    /*
     * Register offset comes from file position.
     */
    reg = (u32)*ppos;

    /*
     * Make sure this is a valid timer register.
     */
    if (!timer_valid_register(reg))
        return -EINVAL;

    /*
     * Read hardware register.
     */
    value = ioread32(timer_base + reg);

    /*
     * Copy result to user space.
     */
    if (copy_to_user(buf, &value, sizeof(value)))
        return -EFAULT;

    return sizeof(value);
}


/* ============================================================
 * WRITE
 *
 * Register offset is supplied through file position.
 *
 * Example:
 *
 *     lseek(fd, TIMER_C1, SEEK_SET);
 *     write(fd, &value, sizeof(value));
 *
 * ============================================================
 */

static ssize_t timer_write(struct file *filp,
                           const char __user *buf,
                           size_t count,
                           loff_t *ppos)
{
    u32 reg;
    u32 value;

    /*
     * Only 32-bit register writes are supported.
     */
    if (count != sizeof(u32))
        return -EINVAL;

    /*
     * Register offset comes from file position.
     */
    reg = (u32)*ppos;

    /*
     * Validate register.
     */
    if (!timer_valid_register(reg))
        return -EINVAL;

    /*
     * CLO and CHI are hardware counters and are read-only.
     */
    if (reg == TIMER_CLO || reg == TIMER_CHI)
        return -EPERM;

    /*
     * Get value from user space.
     */
    if (copy_from_user(&value, buf, sizeof(value)))
        return -EFAULT;

    /*
     * Write hardware register.
     */
    iowrite32(value, timer_base + reg);

    return sizeof(value);
}


/* ============================================================
 * IOCTL
 * ============================================================
 */

static long timer_ioctl(struct file *filp,
                        unsigned int cmd,
                        unsigned long arg)
{
    struct timer_reg reg_data;
    u64 timer_value;
    u32 value;

    switch (cmd) {

    /*
     * --------------------------------------------------------
     * Read timer register
     * --------------------------------------------------------
     *
     * User provides:
     *
     *     struct timer_reg {
     *         .reg = TIMER_CLO
     *     };
     *
     * Driver returns:
     *
     *     .value = register value
     */
    case TIMER_IOC_READ_REG:

        if (copy_from_user(&reg_data,
                           (void __user *)arg,
                           sizeof(reg_data)))
            return -EFAULT;

        if (!timer_valid_register(reg_data.reg))
            return -EINVAL;

        reg_data.value =
            ioread32(timer_base + reg_data.reg);

        if (copy_to_user((void __user *)arg,
                         &reg_data,
                         sizeof(reg_data)))
            return -EFAULT;

        return 0;


    /*
     * --------------------------------------------------------
     * Write timer register
     * --------------------------------------------------------
     */
    case TIMER_IOC_WRITE_REG:

        if (copy_from_user(&reg_data,
                           (void __user *)arg,
                           sizeof(reg_data)))
            return -EFAULT;

        if (!timer_valid_register(reg_data.reg))
            return -EINVAL;

        /*
         * Counter registers are read-only.
         */
        if (reg_data.reg == TIMER_CLO ||
            reg_data.reg == TIMER_CHI)
            return -EPERM;

        iowrite32(reg_data.value,
                  timer_base + reg_data.reg);

        return 0;


    /*
     * --------------------------------------------------------
     * Get 64-bit timer value
     * --------------------------------------------------------
     *
     * System timer:
     *
     *     CHI:CLO
     *
     * We use high-low-high to avoid getting an inconsistent
     * value when CLO rolls over.
     */
    case TIMER_IOC_GET_TIME:
    {
        u32 hi1;
        u32 lo;
        u32 hi2;

        do {
            hi1 = ioread32(timer_base + TIMER_CHI);

            lo = ioread32(timer_base + TIMER_CLO);

            hi2 = ioread32(timer_base + TIMER_CHI);

        } while (hi1 != hi2);

        timer_value = ((u64)hi1 << 32) | lo;

        if (copy_to_user((void __user *)arg,
                         &timer_value,
                         sizeof(timer_value)))
            return -EFAULT;

        return 0;
    }


    /*
     * --------------------------------------------------------
     * Clear timer status
     * --------------------------------------------------------
     *
     * System timer CS register:
     *
     *     bit 0 -> C0 match
     *     bit 1 -> C1 match
     *     bit 2 -> C2 match
     *     bit 3 -> C3 match
     *
     * Writing 1 clears the corresponding status bit.
     */
    case TIMER_IOC_CLEAR_STATUS:

        if (copy_from_user(&value,
                           (void __user *)arg,
                           sizeof(value)))
            return -EFAULT;

        /*
         * Only bits 0-3 are allowed.
         */
        value &= 0xF;

        iowrite32(value, timer_base + TIMER_CS);

        return 0;


    /*
     * --------------------------------------------------------
     * Unknown ioctl
     * --------------------------------------------------------
     */
    default:
        return -ENOTTY;
    }
}


/* ============================================================
 * MMAP
 *
 * Maps timer registers directly into user space.
 *
 * ============================================================
 */

static int timer_mmap(struct file *filp,
                      struct vm_area_struct *vma)
{
    unsigned long size;
    unsigned long pfn;

    /*
     * Size requested by user.
     */
    size = vma->vm_end - vma->vm_start;

    if (size > TIMER_SIZE) {
        pr_err("timer_mmap: mmap size too large\n");
        return -EINVAL;
    }

    /*
     * Physical page frame number.
     */
    pfn = TIMER_BASE_ADDR >> PAGE_SHIFT;

    /*
     * MMIO memory must not be cached.
     */
    vma->vm_page_prot =
        pgprot_noncached(vma->vm_page_prot);

    /*
     * Map physical timer registers into user space.
     */
    if (remap_pfn_range(vma,
                        vma->vm_start,
                        pfn,
                        size,
                        vma->vm_page_prot)) {

        pr_err("timer_mmap: remap_pfn_range failed\n");

        return -EIO;
    }

    return 0;
}


/* ============================================================
 * File operations
 * ============================================================
 */

static const struct file_operations timer_fops = {
    .owner          = THIS_MODULE,

    .open           = timer_open,
    .release        = timer_release,

    .read           = timer_read,
    .write          = timer_write,

    .unlocked_ioctl = timer_ioctl,

    .mmap           = timer_mmap,

    .llseek         = default_llseek,
};


/* ============================================================
 * Module initialization
 * ============================================================
 */

static int __init timer_init(void)
{
    int ret;

    pr_info("timer_mmap: initializing driver\n");

    /*
     * --------------------------------------------------------
     * Map timer registers into kernel virtual address space.
     * --------------------------------------------------------
     */
    timer_base = ioremap(TIMER_BASE_ADDR, TIMER_SIZE);

    if (!timer_base) {
        pr_err("timer_mmap: ioremap failed\n");
        return -ENOMEM;
    }

    pr_info("timer_mmap: timer mapped at %p\n",
            timer_base);


    /*
     * --------------------------------------------------------
     * Allocate character device number.
     * --------------------------------------------------------
     */
    ret = alloc_chrdev_region(&dev_num,
                              0,
                              1,
                              DEVICE_NAME);

    if (ret < 0) {

        pr_err("timer_mmap: alloc_chrdev_region failed\n");

        iounmap(timer_base);

        return ret;
    }


    /*
     * --------------------------------------------------------
     * Initialize character device.
     * --------------------------------------------------------
     */
    cdev_init(&timer_cdev, &timer_fops);

    timer_cdev.owner = THIS_MODULE;

    ret = cdev_add(&timer_cdev,
                   dev_num,
                   1);

    if (ret < 0) {

        pr_err("timer_mmap: cdev_add failed\n");

        unregister_chrdev_region(dev_num, 1);

        iounmap(timer_base);

        return ret;
    }


    /*
     * --------------------------------------------------------
     * Create device class.
     * --------------------------------------------------------
     */
    timer_class = class_create(DEVICE_NAME);

    if (IS_ERR(timer_class)) {

        pr_err("timer_mmap: class_create failed\n");

        cdev_del(&timer_cdev);

        unregister_chrdev_region(dev_num, 1);

        iounmap(timer_base);

        return PTR_ERR(timer_class);
    }


    /*
     * --------------------------------------------------------
     * Create /dev/timer_mmap
     * --------------------------------------------------------
     */
    if (IS_ERR(device_create(timer_class,
                             NULL,
                             dev_num,
                             NULL,
                             DEVICE_NAME))) {

        pr_err("timer_mmap: device_create failed\n");

        class_destroy(timer_class);

        cdev_del(&timer_cdev);

        unregister_chrdev_region(dev_num, 1);

        iounmap(timer_base);

        return -ENOMEM;
    }


    pr_info("timer_mmap: driver initialized\n");
    pr_info("timer_mmap: device /dev/%s\n",
            DEVICE_NAME);

    return 0;
}


/* ============================================================
 * Module cleanup
 * ============================================================
 */

static void __exit timer_exit(void)
{
    pr_info("timer_mmap: removing driver\n");

    /*
     * Remove /dev/timer_mmap.
     */
    device_destroy(timer_class, dev_num);

    /*
     * Destroy class.
     */
    class_destroy(timer_class);

    /*
     * Remove character device.
     */
    cdev_del(&timer_cdev);

    /*
     * Release device number.
     */
    unregister_chrdev_region(dev_num, 1);

    /*
     * Unmap timer registers.
     */
    if (timer_base)
        iounmap(timer_base);

    pr_info("timer_mmap: driver removed\n");
}


/* ============================================================
 * Module information
 * ============================================================
 */

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ChatGPT");
MODULE_DESCRIPTION(
    "Raspberry Pi System Timer Character Device Driver"
);
MODULE_VERSION("1.0");
