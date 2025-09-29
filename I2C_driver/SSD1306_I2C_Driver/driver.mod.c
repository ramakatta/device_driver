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
	{ 0x41ff818d, "i2c_get_adapter" },
	{ 0xd3c72a8c, "i2c_new_client_device" },
	{ 0x1d1d7987, "i2c_register_driver" },
	{ 0x475f5793, "i2c_put_adapter" },
	{ 0x92997ed8, "_printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x56c5da6f, "i2c_unregister_device" },
	{ 0xd9305ff7, "i2c_del_driver" },
	{ 0x96455b51, "i2c_transfer_buffer_flags" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0xf9a482f9, "msleep" },
	{ 0x5aca0882, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:ETX_OLED");

MODULE_INFO(srcversion, "E164B8BE9C4BB13393F2350");
