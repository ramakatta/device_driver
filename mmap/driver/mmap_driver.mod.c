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
	{ 0x76c79894, "remap_pfn_range" },
	{ 0x92997ed8, "_printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xf6e1d11f, "cdev_init" },
	{ 0x42041a93, "cdev_add" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xf795a77a, "class_create" },
	{ 0x4e54674e, "cdev_del" },
	{ 0xa1f37586, "device_create" },
	{ 0xe62f7f62, "device_destroy" },
	{ 0x7057799f, "class_destroy" },
	{ 0xf1ce2f51, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D91884C9AB5540988A5A60D");
