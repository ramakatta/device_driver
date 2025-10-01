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
	{ 0x357aaab3, "mutex_lock_interruptible" },
	{ 0x40a621c5, "snprintf" },
	{ 0xf46d5bf3, "mutex_unlock" },
	{ 0x23f25c0a, "__dynamic_pr_debug" },
	{ 0xbd03ed67, "page_offset_base" },
	{ 0xd09b06f5, "kstrtoint" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0xc961346f, "platform_device_register_full" },
	{ 0x678eaed8, "device_create_file" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xd4f60fb2, "device_remove_file" },
	{ 0x79b86010, "platform_device_unregister" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xd272d446, "__fentry__" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x357aaab3,
	0x40a621c5,
	0xf46d5bf3,
	0x23f25c0a,
	0xbd03ed67,
	0xd09b06f5,
	0xbd03ed67,
	0xc961346f,
	0x678eaed8,
	0xd272d446,
	0xd4f60fb2,
	0x79b86010,
	0xe8213e80,
	0xd272d446,
	0xd272d446,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"mutex_lock_interruptible\0"
	"snprintf\0"
	"mutex_unlock\0"
	"__dynamic_pr_debug\0"
	"page_offset_base\0"
	"kstrtoint\0"
	"__ref_stack_chk_guard\0"
	"platform_device_register_full\0"
	"device_create_file\0"
	"__stack_chk_fail\0"
	"device_remove_file\0"
	"platform_device_unregister\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"__fentry__\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "3439644DA726B2EAD052E32");
