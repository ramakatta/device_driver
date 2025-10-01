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
	{ 0x5fa07cc0, "hrtimer_start_range_ns" },
	{ 0x36a36ab1, "hrtimer_cancel" },
	{ 0x2d88a3ab, "cancel_work_sync" },
	{ 0xaef1f20d, "system_wq" },
	{ 0x49733ad6, "queue_work_on" },
	{ 0x5a844b26, "__x86_indirect_thunk_rax" },
	{ 0x49fc4616, "hrtimer_forward" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xfe5422fa, "hrtimer_setup" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x5fa07cc0,
	0x36a36ab1,
	0x2d88a3ab,
	0xaef1f20d,
	0x49733ad6,
	0x5a844b26,
	0x49fc4616,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0xfe5422fa,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"hrtimer_start_range_ns\0"
	"hrtimer_cancel\0"
	"cancel_work_sync\0"
	"system_wq\0"
	"queue_work_on\0"
	"__x86_indirect_thunk_rax\0"
	"hrtimer_forward\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"hrtimer_setup\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "319CBFC5D0E87217B255AF5");
