// ubsan_demo.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/limits.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("UBSan Demo");
MODULE_DESCRIPTION("Module to trigger simple UBSan-detectable undefined behaviour");

/* Use volatile to avoid compile-time constant-folding/optimizations */
static int __init ubsan_demo_init(void)
{
    volatile int zero = 0;
    volatile int big = INT_MAX;
    volatile int out_of_range_shift = 32; /* UB on 32-bit int shift */
    volatile int v;

    pr_info("ubsan_demo: init — running UB tests\n");

    /* 1) Signed integer overflow */
    /* This is undefined behaviour: INT_MAX + 1 */
    v = big + 1;
    pr_info("ubsan_demo: performed INT_MAX + 1 -> %d\n", v);

    /* 2) Shift out-of-bounds (shifting by >= width of type) */
    /* On a 32-bit int, '1 << 32' is UB. On 64-bit kernel 'int' is still 32-bit so still UB. */
    v = 1 << out_of_range_shift;
    pr_info("ubsan_demo: performed 1 << %d -> %d\n", out_of_range_shift, v);

    /* 3) Division by zero */
    /* Danger: may cause trap if UBSan is configured to trap; otherwise, UBSan will log. */
    pr_info("ubsan_demo: about to perform divide-by-zero (1/zero)\n");
    v = 1 / zero; /* UB: division by zero */
    pr_info("ubsan_demo: result of 1/zero -> %d (should not reach here normally)\n", v);

    return 0;
}

static void __exit ubsan_demo_exit(void)
{
    pr_info("ubsan_demo: exit\n");
}

module_init(ubsan_demo_init);
module_exit(ubsan_demo_exit);

