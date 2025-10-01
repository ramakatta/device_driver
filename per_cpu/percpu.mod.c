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
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xbd03ed67, "this_cpu_off" },
	{ 0x7ec472ba, "cpu_number" },
	{ 0x67628f51, "msleep" },
	{ 0x5e505530, "kthread_should_stop" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x40a621c5, "snprintf" },
	{ 0x6e1d36be, "kthread_create_on_cpu" },
	{ 0x630dad60, "wake_up_process" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xd3e9a166, "__cpuhp_setup_state" },
	{ 0xaca12394, "misc_register" },
	{ 0xf296206e, "nr_cpu_ids" },
	{ 0xb5c51982, "__cpu_online_mask" },
	{ 0x86632fd6, "_find_next_bit" },
	{ 0x9f1ccb41, "__cpuhp_remove_state" },
	{ 0xb5c51982, "__cpu_possible_mask" },
	{ 0xd5ad82a1, "misc_deregister" },
	{ 0xd272d446, "__fentry__" },
	{ 0x5ae9ee26, "__per_cpu_offset" },
	{ 0xe8213e80, "_printk" },
	{ 0x0571dc46, "kthread_stop" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x90a48d82,
	0xbd03ed67,
	0x7ec472ba,
	0x67628f51,
	0x5e505530,
	0xbd03ed67,
	0x40a621c5,
	0x6e1d36be,
	0x630dad60,
	0xd272d446,
	0xd3e9a166,
	0xaca12394,
	0xf296206e,
	0xb5c51982,
	0x86632fd6,
	0x9f1ccb41,
	0xb5c51982,
	0xd5ad82a1,
	0xd272d446,
	0x5ae9ee26,
	0xe8213e80,
	0x0571dc46,
	0xd272d446,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__ubsan_handle_out_of_bounds\0"
	"this_cpu_off\0"
	"cpu_number\0"
	"msleep\0"
	"kthread_should_stop\0"
	"__ref_stack_chk_guard\0"
	"snprintf\0"
	"kthread_create_on_cpu\0"
	"wake_up_process\0"
	"__stack_chk_fail\0"
	"__cpuhp_setup_state\0"
	"misc_register\0"
	"nr_cpu_ids\0"
	"__cpu_online_mask\0"
	"_find_next_bit\0"
	"__cpuhp_remove_state\0"
	"__cpu_possible_mask\0"
	"misc_deregister\0"
	"__fentry__\0"
	"__per_cpu_offset\0"
	"_printk\0"
	"kthread_stop\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "01131AB70E3BD1F451FCA2A");
