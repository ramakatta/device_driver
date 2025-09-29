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
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xeb9d7920, "cdev_init" },
	{ 0xf212d1ce, "cdev_add" },
	{ 0x3d568d84, "class_create" },
	{ 0x0cf2b0e8, "device_create" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0x4ac4312d, "kmalloc_caches" },
	{ 0x8d1d7639, "__kmalloc_cache_noprof" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xfbc10eaa, "class_destroy" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0xc68d7731, "device_destroy" },
	{ 0xd2a864c6, "cdev_del" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x9f222e1e,
	0xeb9d7920,
	0xf212d1ce,
	0x3d568d84,
	0x0cf2b0e8,
	0xbd03ed67,
	0x4ac4312d,
	0x8d1d7639,
	0x0bc5fb0d,
	0xfbc10eaa,
	0xcb8b6ec6,
	0xc68d7731,
	0xd2a864c6,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0xa61fd7aa,
	0x092a35a2,
	0x092a35a2,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"unregister_chrdev_region\0"
	"class_destroy\0"
	"kfree\0"
	"device_destroy\0"
	"cdev_del\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"_copy_to_user\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "538CC52AA7BB7C952AA4F6D");
