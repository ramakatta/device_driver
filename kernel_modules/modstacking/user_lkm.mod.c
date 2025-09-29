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
	{ 0xacae9bb1, "get_skey" },
	{ 0x23f25c0a, "__dynamic_pr_debug" },
	{ 0x7ec472ba, "exp_int" },
	{ 0xd272d446, "llkd_sysinfo2" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xacae9bb1,
	0x23f25c0a,
	0x7ec472ba,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"get_skey\0"
	"__dynamic_pr_debug\0"
	"exp_int\0"
	"llkd_sysinfo2\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "core_lkm");


MODULE_INFO(srcversion, "7D7FBC1D8D97C5CF733EC92");
