#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>

#define DEVICE_NAME "timer_mmap"
#define TIMER_BASE_ADDR  0x3F003000  // System timer base address (RPi 4)
#define TIMER_SIZE       0x1000      // Mapping size (4KB)

// Character device variables
static dev_t dev_num;
static struct cdev cdev;
static struct class *timer_class;
static void __iomem *timer_base;

static int timer_open(struct inode *inode, struct file *filp) {
    return 0;
}

static int timer_release(struct inode *inode, struct file *filp) {
    return 0;
}

// mmap operation to expose timer registers to user-space
static int timer_mmap(struct file *filp, struct vm_area_struct *vma) {
    unsigned long offset = TIMER_BASE_ADDR >> PAGE_SHIFT;
    unsigned long size = vma->vm_end - vma->vm_start;

    if (size > TIMER_SIZE) {
        pr_err("Requested mmap size exceeds limit.\n");
        return -EINVAL;
    }

    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

    if (remap_pfn_range(vma, vma->vm_start, offset, size, vma->vm_page_prot)) {
        pr_err("remap_pfn_range failed\n");
        return -EIO;
    }

    return 0;
}

static struct file_operations timer_fops = {
    .owner = THIS_MODULE,
    .open = timer_open,
    .release = timer_release,
    .mmap = timer_mmap,
};

static int __init timer_init(void) {
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("Failed to allocate char device region.\n");
        return ret;
    }

    cdev_init(&cdev, &timer_fops);
    ret = cdev_add(&cdev, dev_num, 1);
    if (ret < 0) {
        pr_err("Failed to add char device.\n");
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    timer_class = class_create(DEVICE_NAME);
    if (IS_ERR(timer_class)) {
        pr_err("Failed to create device class.\n");
        cdev_del(&cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(timer_class);
    }

    device_create(timer_class, NULL, dev_num, NULL, DEVICE_NAME);

    pr_info("Timer mmap driver initialized.\n");
    return 0;
}

static void __exit timer_exit(void) {
    device_destroy(timer_class, dev_num);
    class_destroy(timer_class);
    cdev_del(&cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("Timer mmap driver removed.\n");
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ChatGPT");
MODULE_DESCRIPTION("Raspberry Pi Timer MMAP Kernel Driver");

