#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

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
	{ 0x27126e5a, "module_layout" },
	{ 0xfaad79e, "device_create" },
	{ 0xa00aaa80, "cdev_add" },
	{ 0x159131d9, "cdev_init" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xf57bae51, "kmem_cache_alloc_trace" },
	{ 0x2e8895d0, "kmalloc_caches" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x20dde6b3, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "AD5A5157DBB97960B392937");
