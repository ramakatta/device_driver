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
	{ 0xe8213e80, "_printk" },
	{ 0x058c185a, "jiffies" },
	{ 0x5e505530, "kthread_should_stop" },
	{ 0xd272d446, "schedule" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x7f79e79a, "kthread_create_on_node" },
	{ 0x630dad60, "wake_up_process" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x0571dc46, "kthread_stop" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xe8213e80,
	0x058c185a,
	0x5e505530,
	0xd272d446,
	0xd272d446,
	0xbd03ed67,
	0x7f79e79a,
	0x630dad60,
	0xd272d446,
	0x0571dc46,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"_printk\0"
	"jiffies\0"
	"kthread_should_stop\0"
	"schedule\0"
	"__x86_return_thunk\0"
	"__ref_stack_chk_guard\0"
	"kthread_create_on_node\0"
	"wake_up_process\0"
	"__stack_chk_fail\0"
	"kthread_stop\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A880CF451ADD4010408DF52");
