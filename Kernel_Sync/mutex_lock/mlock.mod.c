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
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x357aaab3, "mutex_lock_interruptible" },
	{ 0x67628f51, "msleep" },
	{ 0xf46d5bf3, "mutex_unlock" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xf46d5bf3, "mutex_lock" },
	{ 0xd5ad82a1, "misc_deregister" },
	{ 0xd272d446, "__fentry__" },
	{ 0xaca12394, "misc_register" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xbd03ed67,
	0x092a35a2,
	0x357aaab3,
	0x67628f51,
	0xf46d5bf3,
	0xd272d446,
	0xf46d5bf3,
	0xd5ad82a1,
	0xd272d446,
	0xaca12394,
	0xe8213e80,
	0xd272d446,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__ref_stack_chk_guard\0"
	"_copy_from_user\0"
	"mutex_lock_interruptible\0"
	"msleep\0"
	"mutex_unlock\0"
	"__stack_chk_fail\0"
	"mutex_lock\0"
	"misc_deregister\0"
	"__fentry__\0"
	"misc_register\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "94CBD21D512EAE49A80DC33");
