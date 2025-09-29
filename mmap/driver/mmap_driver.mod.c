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
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x40494c96, "remap_pfn_range" },
	{ 0x92997ed8, "_printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x69076583, "cdev_init" },
	{ 0x739429ec, "cdev_add" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x5fb99ccd, "class_create" },
	{ 0x167816b1, "cdev_del" },
	{ 0x22fe2c6e, "device_create" },
	{ 0x92b31d59, "device_destroy" },
	{ 0xceee1cfb, "class_destroy" },
	{ 0x5aca0882, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D91884C9AB5540988A5A60D");
