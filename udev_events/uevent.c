#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/kobject.h>
#include <linux/string.h>

#define DRIVER_NAME "uevent_sender"
#define DEVICE_COUNT 1
#define EVENT_ACTION "change"

// --- Global Variables ---
static dev_t uevent_dev_t;
static struct cdev uevent_cdev;
static struct class *uevent_class;
static struct device *uevent_device;

// --- Function Prototypes ---
ssize_t uevent_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);
int uevent_open(struct inode *inode, struct file *file);
int uevent_release(struct inode *inode, struct file *file);

// --- File Operations Structure ---
static const struct file_operations uevent_fops = {
    .owner = THIS_MODULE,
    .open = uevent_open,
    .release = uevent_release,
    .write = uevent_write,
};

/**
 * @brief Sends a custom uevent to userspace (udev).
 *
 * This function uses kobject_uevent_env to send an event.
 * The core environment variables are:
 * - ACTION: "change" (to trigger udev rules)
 * - CUSTOM_EVENT: "1" (our specific identifier)
 * - DRIVER_PID: The PID of the userspace process writing to the device (if applicable)
 *
 * @return 0 on success, negative error code otherwise.
 */
static int send_custom_uevent(void)
{
    int ret;
    char *envp[3]; // We need 3 environment strings: ACTION, CUSTOM_EVENT, and a NULL terminator.

    // 1. Set the primary ACTION for the udev rule to match
    envp[0] = "ACTION=" EVENT_ACTION;

    // 2. Set our custom variable for specific script execution
    envp[1] = "CUSTOM_EVENT=1";

    // 3. Null terminator
    envp[2] = NULL;

    // Send the event. We use KOBJ_CHANGE to correspond with ACTION=change.
    ret = kobject_uevent_env(&uevent_device->kobj, KOBJ_CHANGE, envp);

    if (ret == 0) {
        pr_info("%s: Successfully sent uevent (ACTION=%s, CUSTOM_EVENT=1).\n", DRIVER_NAME, EVENT_ACTION);
    } else {
        pr_err("%s: Failed to send uevent, error: %d\n", DRIVER_NAME, ret);
    }

    return ret;
}

// --- Device File Handlers ---

int uevent_open(struct inode *inode, struct file *file)
{
    pr_info("%s: Device opened.\n", DRIVER_NAME);
    return 0;
}

int uevent_release(struct inode *inode, struct file *file)
{
    pr_info("%s: Device closed.\n", DRIVER_NAME);
    return 0;
}

ssize_t uevent_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
    pr_info("%s: Write received, triggering uevent...\n", DRIVER_NAME);
    send_custom_uevent();
    // We consumed the write, return the length of data written
    return len; 
}


// --- Module Init and Exit ---

static int __init uevent_driver_init(void)
{
    int ret;

    // 1. Allocate major/minor numbers
    ret = alloc_chrdev_region(&uevent_dev_t, 0, DEVICE_COUNT, DRIVER_NAME);
    if (ret < 0) {
        pr_err("%s: Failed to allocate char device region: %d\n", DRIVER_NAME, ret);
        return ret;
    }

    // 2. Initialize and add character device
    cdev_init(&uevent_cdev, &uevent_fops);
    uevent_cdev.owner = THIS_MODULE;
    ret = cdev_add(&uevent_cdev, uevent_dev_t, DEVICE_COUNT);
    if (ret < 0) {
        pr_err("%s: Failed to add char device: %d\n", DRIVER_NAME, ret);
        goto unreg_chrdev;
    }

    // 3. Create device class (for automatic device node creation)
    uevent_class = class_create(DRIVER_NAME);
    if (IS_ERR(uevent_class)) {
        pr_err("%s: Failed to create device class.\n", DRIVER_NAME);
        ret = PTR_ERR(uevent_class);
        goto cdev_del;
    }

    // 4. Create device node /dev/uevent_sender
    // This is the kobject whose name (uevent_sender) and path (dev/uevent_sender)
    // udev will use to identify the device.
    uevent_device = device_create(uevent_class, NULL, uevent_dev_t, NULL, DRIVER_NAME);
    if (IS_ERR(uevent_device)) {
        pr_err("%s: Failed to create device.\n", DRIVER_NAME);
        ret = PTR_ERR(uevent_device);
        goto class_destroy;
    }

    pr_info("%s: Driver loaded successfully. Device: /dev/%s\n", DRIVER_NAME, DRIVER_NAME);
    return 0;

class_destroy:
    class_destroy(uevent_class);
cdev_del:
    cdev_del(&uevent_cdev);
unreg_chrdev:
    unregister_chrdev_region(uevent_dev_t, DEVICE_COUNT);
    return ret;
}

static void __exit uevent_driver_exit(void)
{
    device_destroy(uevent_class, uevent_dev_t);
    class_destroy(uevent_class);
    cdev_del(&uevent_cdev);
    unregister_chrdev_region(uevent_dev_t, DEVICE_COUNT);
    pr_info("%s: Driver unloaded.\n", DRIVER_NAME);
}

module_init(uevent_driver_init);
module_exit(uevent_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Opensource");
MODULE_DESCRIPTION("A simple character driver to send custom uevents to udev.");

