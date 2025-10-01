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
	{ 0xd272d446, "__fentry__" },
	{ 0xf5bae445, "__virt_addr_valid" },
	{ 0xbd03ed67, "page_offset_base" },
	{ 0xbd03ed67, "phys_base" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x6bded543, "get_free_pages_noprof" },
	{ 0x48fd0ca0, "get_zeroed_page_noprof" },
	{ 0xb54d37ac, "alloc_pages_noprof" },
	{ 0xbd03ed67, "vmemmap_base" },
	{ 0xc2614bbe, "param_ops_int" },
	{ 0xe8213e80, "_printk" },
	{ 0x02e1dca7, "free_pages" },
	{ 0xba157484, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0xd272d446,
	0xf5bae445,
	0xbd03ed67,
	0xbd03ed67,
	0xd272d446,
	0x6bded543,
	0x48fd0ca0,
	0xb54d37ac,
	0xbd03ed67,
	0xc2614bbe,
	0xe8213e80,
	0x02e1dca7,
	0xba157484,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__x86_return_thunk\0"
	"__fentry__\0"
	"__virt_addr_valid\0"
	"page_offset_base\0"
	"phys_base\0"
	"__stack_chk_fail\0"
	"get_free_pages_noprof\0"
	"get_zeroed_page_noprof\0"
	"alloc_pages_noprof\0"
	"vmemmap_base\0"
	"param_ops_int\0"
	"_printk\0"
	"free_pages\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "6DCD339DFA3F4856A875932");
