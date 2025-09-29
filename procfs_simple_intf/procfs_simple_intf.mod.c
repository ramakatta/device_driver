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
	{ 0x5c3c7387, "kstrtoull" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xdfcac0d2, "single_open" },
	{ 0xb4b312e4, "seq_printf" },
	{ 0x7cd8d75e, "page_offset_base" },
	{ 0x8c8569cb, "kstrtoint" },
	{ 0x9da58f1, "proc_mkdir" },
	{ 0x83557adc, "proc_create" },
	{ 0x50c6df9c, "proc_create_single_data" },
	{ 0x4c03a563, "random_kmalloc_seed" },
	{ 0xcb742157, "kmalloc_caches" },
	{ 0xfe1d3f1a, "kmalloc_trace" },
	{ 0x52821b6d, "seq_read" },
	{ 0xa797d86c, "seq_lseek" },
	{ 0xcb1b2a3c, "single_release" },
	{ 0x42c8c17a, "remove_proc_subtree" },
	{ 0x37a0cba, "kfree" },
	{ 0x122c3a7e, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x89940875, "mutex_lock_interruptible" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x2cf56265, "__dynamic_pr_debug" },
	{ 0x8d5e53af, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "3929B59AA746223D4AB3823");
