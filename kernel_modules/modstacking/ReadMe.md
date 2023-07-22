 * This kernel module - user_lkm - is part of the 'modstacking' POC project:
 *    user_lkm           [<--- this code]
 *        |
 *    core_lkm
 * The user_lkm kernel module calls an (exported) function that resides
 * in the core_lkm kernel module.

To insert module in the kernel:
insmod core_lkm.ko
insmod user_lkm.ko

OR

modprobe user_lkm

To remove module from the kernel:
rmmod core_lkm.ko
rmmod user_lkm.ko


