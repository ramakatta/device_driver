// SPDX-License-Identifier: GPL-2.0

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/types.h>

#include <linux/arm-smccc.h>
#include "clock_smc.h"

#define RPI4_SMC_SUCCESS 0
#define RPI4_SMC_UNKOWN  0xffffffffU

/*
 * ============================================================
 * SMC helper
 * ============================================================
 *
 * x0 = SMC function ID
 *
 * TF-A returns the requested value in x0.
 */

static long rpi4_smc_call(unsigned long smc_id)
{
    struct arm_smccc_res res;

    arm_smccc_smc(
        smc_id,       /* x0 */
        0,            /* x1 */
        0,            /* x2 */
        0,            /* x3 */
        0,            /* x4 */
        0,            /* x5 */
        0,            /* x6 */
        0,            /* x7 */
        &res
    );
    if((u32)res.a0 == RPI4_SMC_UNKOWN)
       return -ENOTTY;
     if((u32)res.a0 != RPI4_SMC_SUCCESS)
       return -EIO;
    return (long)res.a1;
}


/*
 * ============================================================
 * IOCTL handler
 * ============================================================
 */

static long rpi4_clock_ioctl(
    struct file *file,
    unsigned int cmd,
    unsigned long arg)
{
    __u64 value;

    switch (cmd) {

    /*
     * --------------------------------------------------------
     * Get counter frequency
     * --------------------------------------------------------
     */
    case RPI4_CLOCK_GET_FREQ:

        pr_info("rpi4_clock: GET_FREQ\n");

        value = (__u64)rpi4_smc_call(
            RPI4_SMC_GET_FREQ);
        if (value < 0) {
            return value; // Passes -EIO (-5) or -ENOTTY to user apps properly
        }
        if (copy_to_user(
                (void __user *)arg,
                &value,
                sizeof(value))) {

            pr_err("rpi4_clock: copy_to_user failed\n");
            return -EFAULT;
        }

        break;


    /*
     * --------------------------------------------------------
     * Get physical counter
     * --------------------------------------------------------
     */
    case RPI4_CLOCK_GET_COUNT:

        pr_info("rpi4_clock: GET_COUNT\n");

        value = (__u64)rpi4_smc_call(
            RPI4_SMC_GET_COUNT);
        if (value < 0) {
            return value; // Passes -EIO (-5) or -ENOTTY to user apps properly
        }
        if (copy_to_user(
                (void __user *)arg,
                &value,
                sizeof(value))) {

            pr_err("rpi4_clock: copy_to_user failed\n");
            return -EFAULT;
        }

        break;


    default:

        pr_err(
            "rpi4_clock: unknown ioctl 0x%x\n",
            cmd);

        return -EINVAL;
    }

    return 0;
}


/*
 * ============================================================
 * File operations
 * ============================================================
 */

static const struct file_operations rpi4_clock_fops = {
    .owner          = THIS_MODULE,
    .unlocked_ioctl = rpi4_clock_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = rpi4_clock_ioctl,
#endif
};


/*
 * ============================================================
 * Misc device
 * ============================================================
 */

static struct miscdevice rpi4_clock_miscdev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name  = "rpi4_clock",
    .fops  = &rpi4_clock_fops,
    .mode  = 0600,
};


/*
 * ============================================================
 * Module init
 * ============================================================
 */

static int __init rpi4_clock_init(void)
{
    int ret;

    pr_info("rpi4_clock: module loading\n");

    ret = misc_register(&rpi4_clock_miscdev);

    if (ret) {
        pr_err(
            "rpi4_clock: misc_register failed: %d\n",
            ret);

        return ret;
    }

    pr_info(
        "rpi4_clock: /dev/rpi4_clock created\n");

    return 0;
}


/*
 * ============================================================
 * Module exit
 * ============================================================
 */

static void __exit rpi4_clock_exit(void)
{
    misc_deregister(&rpi4_clock_miscdev);

    pr_info("rpi4_clock: module unloaded\n");
}


module_init(rpi4_clock_init);
module_exit(rpi4_clock_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rama");
MODULE_DESCRIPTION(
    "Raspberry Pi 4 clock SMC driver");
MODULE_VERSION("1.0");
