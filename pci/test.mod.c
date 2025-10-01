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
	{ 0xe5c2991b, "__pci_register_driver" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x405cdbdf, "pci_read_config_word" },
	{ 0x2437d1be, "pci_enable_device" },
	{ 0x381ea112, "pci_request_region" },
	{ 0xf145940c, "pci_iomap" },
	{ 0xef036183, "pci_release_regions" },
	{ 0x201d9cdc, "pci_disable_device" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x2b6f53b9, "pci_unregister_driver" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe8213e80, "_printk" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xe5c2991b,
	0xbd03ed67,
	0x405cdbdf,
	0x2437d1be,
	0x381ea112,
	0xf145940c,
	0xef036183,
	0x201d9cdc,
	0xd272d446,
	0x2b6f53b9,
	0xd272d446,
	0xe8213e80,
	0xd272d446,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__pci_register_driver\0"
	"__ref_stack_chk_guard\0"
	"pci_read_config_word\0"
	"pci_enable_device\0"
	"pci_request_region\0"
	"pci_iomap\0"
	"pci_release_regions\0"
	"pci_disable_device\0"
	"__stack_chk_fail\0"
	"pci_unregister_driver\0"
	"__fentry__\0"
	"_printk\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");

MODULE_ALIAS("pci:v000010ECd00008129sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010ECd00008136sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010ECd00008167sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010ECd00008168sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010ECd00008169sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004300sv00001186sd00004B10bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004300sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001186d00004302sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001259d0000C107sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000016ECd00000116sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00001737d00001032sv*sd00000024bc*sc*i*");
MODULE_ALIAS("pci:v00000001d00008168sv*sd00002410bc*sc*i*");

MODULE_INFO(srcversion, "99BF5B2ED9632EE3CA9AA4D");
