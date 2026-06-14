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
	{ 0x92997ed8, "_printk" },
	{ 0x4302d0eb, "free_pages" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xccf69887, "get_free_pages_noprof" },
	{ 0x8f14d45b, "get_zeroed_page_noprof" },
	{ 0x308416ce, "__alloc_pages_noprof" },
	{ 0xe9b836d3, "mem_map" },
	{ 0x987c11c7, "__pv_phys_pfn_offset" },
	{ 0x2d7d2346, "param_ops_int" },
	{ 0xf1ce2f51, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "ED5A8D7CDFD3A3FDBC036E9");
