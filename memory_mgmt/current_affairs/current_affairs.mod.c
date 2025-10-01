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
	{ 0x2719b9fa, "const_current_task" },
	{ 0xa66ba6c3, "init_user_ns" },
	{ 0x30d7a49c, "from_kuid" },
	{ 0x7ec472ba, "__preempt_count" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x2719b9fa,
	0xa66ba6c3,
	0x30d7a49c,
	0x7ec472ba,
	0xd272d446,
	0xd272d446,
	0xe8213e80,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"const_current_task\0"
	"init_user_ns\0"
	"from_kuid\0"
	"__preempt_count\0"
	"__x86_return_thunk\0"
	"__fentry__\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "18A6E8D905BB2C148A8E20A");
