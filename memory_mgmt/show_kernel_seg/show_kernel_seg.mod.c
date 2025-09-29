#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
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

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xc358aaf8, "snprintf" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x92997ed8, "_printk" },
	{ 0x8a7d1c31, "high_memory" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x5f754e5a, "memset" },
	{ 0xdd0a2ba2, "strlcat" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xa086ce25, "param_ops_int" },
	{ 0x5aca0882, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "4A9DF2B086C9AC357DE9E86");
