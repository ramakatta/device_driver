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

KSYMTAB_DATA(exp_int, "_gpl", "");
KSYMTAB_FUNC(llkd_sysinfo2, "", "");
KSYMTAB_FUNC(get_skey, "", "");

SYMBOL_CRC(exp_int, 0x7ec472ba, "_gpl");
SYMBOL_CRC(llkd_sysinfo2, 0xd272d446, "");
SYMBOL_CRC(get_skey, 0xacae9bb1, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0x40a621c5, "snprintf" },
	{ 0x9479a1e8, "strnlen" },
	{ 0xe54e0a6b, "__fortify_panic" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x70eca2ca, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0x40a621c5,
	0x9479a1e8,
	0xe54e0a6b,
	0xd272d446,
	0x70eca2ca,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"snprintf\0"
	"strnlen\0"
	"__fortify_panic\0"
	"__stack_chk_fail\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5246B028628CA90005DADD9");
