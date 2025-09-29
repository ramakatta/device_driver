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
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__rcu_read_lock" },
	{ 0xa2152099, "init_task" },
	{ 0x40a621c5, "snprintf" },
	{ 0x7851be11, "__SCT__cond_resched" },
	{ 0xd272d446, "__rcu_read_unlock" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xd272d446,
	0xa2152099,
	0x40a621c5,
	0x7851be11,
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"__rcu_read_lock\0"
	"init_task\0"
	"snprintf\0"
	"__SCT__cond_resched\0"
	"__rcu_read_unlock\0"
	"__stack_chk_fail\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "B06EA060E9AFC168D69FC9B");
