#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x92997ed8, "_printk" },
	{ 0xc6cbbc89, "capable" },
	{ 0x5f754e5a, "memset" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x99712871, "gpio_to_desc" },
	{ 0x4ee7ad90, "gpiod_direction_output_raw" },
	{ 0x20f02edf, "gpiod_export" },
	{ 0x1c714cb5, "gpiod_get_raw_value" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x5d1ee975, "gpiod_set_raw_value" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8dab4621, "kmalloc_caches" },
	{ 0xf795a77a, "class_create" },
	{ 0x604324bd, "__kmalloc_cache_noprof" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xf6e1d11f, "cdev_init" },
	{ 0x42041a93, "cdev_add" },
	{ 0xa1f37586, "device_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe62f7f62, "device_destroy" },
	{ 0x4e54674e, "cdev_del" },
	{ 0x37a0cba, "kfree" },
	{ 0xfe990052, "gpio_free" },
	{ 0x7057799f, "class_destroy" },
	{ 0xf1ce2f51, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "7AA4EEB9DCE6D70DEA77E39");
