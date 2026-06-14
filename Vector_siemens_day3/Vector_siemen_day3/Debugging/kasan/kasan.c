// kasan_demo.c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

static int __init kasan_demo_init(void)
{
    char *buf;

    pr_info("kasan_demo: loading (will trigger KASAN)...\n");

    buf = kmalloc(16, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    pr_info("kasan_demo: allocated 16 bytes at %p\n", buf);

    /* Intentional out-of-bounds write */
    buf[16] = 'X';

    pr_info("kasan_demo: wrote past buffer end, expect KASAN report\n");

    kfree(buf);

    return 0;
}

static void __exit kasan_demo_exit(void)
{
    pr_info("kasan_demo: unloading\n");
}

module_init(kasan_demo_init);
module_exit(kasan_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KASAN Demo");
MODULE_DESCRIPTION("Kernel module that intentionally triggers a KASAN bug");

