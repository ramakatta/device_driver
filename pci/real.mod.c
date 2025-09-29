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
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xd6c83743, "pci_iounmap" },
	{ 0xc5169084, "pci_release_regions" },
	{ 0xd61983dd, "pci_disable_device" },
	{ 0x3c9c904a, "pci_read_config_word" },
	{ 0x9d627daf, "pci_enable_device" },
	{ 0x25aeb952, "pci_request_regions" },
	{ 0x5769e406, "pci_iomap" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xc5e89969, "pci_unregister_driver" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x122c3a7e, "_printk" },
	{ 0xdd8f2bd9, "__pci_register_driver" },
	{ 0x6ad2b3e, "module_layout" },
};

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

MODULE_INFO(srcversion, "3A12E52DB137AA4046BD4B8");
