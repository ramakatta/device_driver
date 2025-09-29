#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__

#include <linux/init.h>
#include <linux/module.h>
#ifdef CONFIG_X86
#include <asm/fpu/api.h>
#endif

#ifdef CONFIG_ARM64
#include <asm/neon.h>
#define kernel_fpu_begin kernel_neon_begin
#define kernel_fpu_end kernel_neon_end
#endif

MODULE_AUTHOR("Open source");
MODULE_DESCRIPTION("fp_in_lkm: no performing FP \
(floating point) arithmetic in kernel mode");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.2");

static double num = 22.0, den = 7.0, mypi;

static int __init fp_in_lkm_init(void)
{
	pr_info("inserted\n");

	kernel_fpu_begin();
	mypi = num / den;
	kernel_fpu_end();
#if 1
	pr_info("PI = %.4f = %.4f\n", mypi, num / den);
#endif

	return 0;		/* success */
}

static void __exit fp_in_lkm_exit(void)
{
	kernel_fpu_begin();
	pr_info("mypi = %f\n", mypi);
	kernel_fpu_end();

	pr_info("removed\n");
}

module_init(fp_in_lkm_init);
module_exit(fp_in_lkm_exit);
