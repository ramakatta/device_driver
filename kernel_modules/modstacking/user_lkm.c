#define pr_fmt(fmt) "%s:%s(): " fmt, KBUILD_MODNAME, __func__

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

extern void llkd_sysinfo2(void);
extern long get_skey(int);
extern int exp_int;
#define THE_ONE   0xfedface

/* Call some functions within the 'core' module */
static int __init user_lkm_init(void)
{
	pr_info("inserted\n");
	u64 sk = get_skey(THE_ONE);

	pr_debug("Called get_skey(), ret = 0x%llx = %llu\n", sk, sk);
	printk(KERN_DEBUG "Called get_skey(), ret = 0x%llx = %llu\n", sk, sk);
	pr_debug("exp_int = %d\n", exp_int);
	llkd_sysinfo2();

	return 0;
}

static void __exit user_lkm_exit(void)
{
	pr_info("bids you adieu\n");
	printk(KERN_INFO"bids you adieu\n");
}

module_init(user_lkm_init);
module_exit(user_lkm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMA");
MODULE_DESCRIPTION("A API usage module.");
