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
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x2d57e435, "pcpu_hot" },
	{ 0x53569707, "this_cpu_off" },
	{ 0xf9a482f9, "msleep" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xbddfea60, "kthread_create_on_cpu" },
	{ 0x8ef6d02c, "wake_up_process" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x2aadffd3, "__cpuhp_setup_state" },
	{ 0x568c36f3, "misc_register" },
	{ 0x875e9ebe, "__cpuhp_remove_state" },
	{ 0x17de3d5, "nr_cpu_ids" },
	{ 0x5a5a2271, "__cpu_online_mask" },
	{ 0x53a1e8d9, "_find_next_bit" },
	{ 0xef9ac92d, "misc_deregister" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xb19a5453, "__per_cpu_offset" },
	{ 0x68bdb9a6, "kthread_stop" },
	{ 0x122c3a7e, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xb2b23fc2, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "B1551F1EF37E4E385C343A6");
