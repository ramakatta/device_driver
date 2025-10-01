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
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0xd5f66efd, "cdev_init" },
	{ 0x8ea73856, "cdev_add" },
	{ 0x653aa194, "class_create" },
	{ 0xe486c4b7, "device_create" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0xfaabfe5e, "kmalloc_caches" },
	{ 0xc064623f, "__kmalloc_cache_noprof" },
	{ 0x7ec472ba, "__preempt_count" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0xa1dacb42, "class_destroy" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0x1595e410, "device_destroy" },
	{ 0x4e54d6ac, "cdev_del" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x546c19d9, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x092a35a2,
	0x9f222e1e,
	0xd5f66efd,
	0x8ea73856,
	0x653aa194,
	0xe486c4b7,
	0xbd03ed67,
	0xfaabfe5e,
	0xc064623f,
	0x7ec472ba,
	0x0bc5fb0d,
	0xa1dacb42,
	0xcb8b6ec6,
	0x1595e410,
	0x4e54d6ac,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x546c19d9,
	0xa61fd7aa,
	0x092a35a2,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"_copy_to_user\0"
	"alloc_chrdev_region\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"__preempt_count\0"
	"unregister_chrdev_region\0"
	"class_destroy\0"
	"kfree\0"
	"device_destroy\0"
	"cdev_del\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8F9D116D0B0E618E2098EEB");
