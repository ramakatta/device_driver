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
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x7f79e79a, "kthread_create_on_node" },
	{ 0x630dad60, "wake_up_process" },
	{ 0x2520ea93, "refcount_warn_saturate" },
	{ 0x2719b9fa, "const_current_task" },
	{ 0xb2fa43dd, "kernel_sigaction" },
	{ 0x5e505530, "kthread_should_stop" },
	{ 0x5a8347fe, "__tracepoint_sched_set_state_tp" },
	{ 0xd272d446, "schedule" },
	{ 0xb2e62cba, "__trace_set_current_state" },
	{ 0xd272d446, "__fentry__" },
	{ 0x0571dc46, "kthread_stop" },
	{ 0xe8213e80, "_printk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0x7f79e79a,
	0x630dad60,
	0x2520ea93,
	0x2719b9fa,
	0xb2fa43dd,
	0x5e505530,
	0x5a8347fe,
	0xd272d446,
	0xb2e62cba,
	0xd272d446,
	0x0571dc46,
	0xe8213e80,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__x86_return_thunk\0"
	"kthread_create_on_node\0"
	"wake_up_process\0"
	"refcount_warn_saturate\0"
	"const_current_task\0"
	"kernel_sigaction\0"
	"kthread_should_stop\0"
	"__tracepoint_sched_set_state_tp\0"
	"schedule\0"
	"__trace_set_current_state\0"
	"__fentry__\0"
	"kthread_stop\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "48036726D2E93718F6BDFC3");
