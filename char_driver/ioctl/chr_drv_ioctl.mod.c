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
	{ 0xf6389d45, "cdev_alloc" },
	{ 0xeb9d7920, "cdev_init" },
	{ 0xf212d1ce, "cdev_add" },
	{ 0x3d568d84, "class_create" },
	{ 0x0cf2b0e8, "device_create" },
	{ 0xd710adbf, "__kmalloc_noprof" },
	{ 0xd2a864c6, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x27683a56, "memset" },
	{ 0x0c161ddc, "capable" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xc68d7731, "device_destroy" },
	{ 0xfbc10eaa, "class_destroy" },
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xe8213e80, "_printk" },
	{ 0x96c07e76, "const_pcpu_hot" },
	{ 0x9e85405f, "module_refcount" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x092a35a2,
	0x9f222e1e,
	0xf6389d45,
	0xeb9d7920,
	0xf212d1ce,
	0x3d568d84,
	0x0cf2b0e8,
	0xd710adbf,
	0xd2a864c6,
	0x0bc5fb0d,
	0x27683a56,
	0x0c161ddc,
	0x092a35a2,
	0xcb8b6ec6,
	0xd272d446,
	0xc68d7731,
	0xfbc10eaa,
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0x96c07e76,
	0x9e85405f,
	0xa61fd7aa,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"_copy_to_user\0"
	"alloc_chrdev_region\0"
	"cdev_alloc\0"
	"cdev_init\0"
	"cdev_add\0"
	"class_create\0"
	"device_create\0"
	"__kmalloc_noprof\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"memset\0"
	"capable\0"
	"_copy_from_user\0"
	"kfree\0"
	"__stack_chk_fail\0"
	"device_destroy\0"
	"class_destroy\0"
	"__fentry__\0"
	"__x86_return_thunk\0"
	"_printk\0"
	"const_pcpu_hot\0"
	"module_refcount\0"
	"__check_object_size\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C4CB838E7EAB32705BF88CD");
