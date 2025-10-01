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
	{ 0x16ab4215, "__wake_up" },
	{ 0xe8213e80, "_printk" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x5e505530, "kthread_should_stop" },
	{ 0x7851be11, "__SCT__might_resched" },
	{ 0x7a5ffe84, "init_wait_entry" },
	{ 0xd272d446, "schedule" },
	{ 0x0db8d68d, "prepare_to_wait_event" },
	{ 0xc87f4bab, "finish_wait" },
	{ 0x9d33f583, "kill_fasync" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x9c0551c6, "__tasklet_schedule" },
	{ 0xf2f79e52, "fasync_helper" },
	{ 0x9f222e1e, "alloc_chrdev_region" },
	{ 0x653aa194, "class_create" },
	{ 0xd5f66efd, "cdev_init" },
	{ 0x8ea73856, "cdev_add" },
	{ 0xe486c4b7, "device_create" },
	{ 0x5403c125, "__init_waitqueue_head" },
	{ 0xcdec1689, "tasklet_init" },
	{ 0x7f79e79a, "kthread_create_on_node" },
	{ 0x630dad60, "wake_up_process" },
	{ 0x9126ce86, "request_threaded_irq" },
	{ 0x4e54d6ac, "cdev_del" },
	{ 0x0bc5fb0d, "unregister_chrdev_region" },
	{ 0x1595e410, "device_destroy" },
	{ 0xa1dacb42, "class_destroy" },
	{ 0x0571dc46, "kthread_stop" },
	{ 0x9dd4105e, "free_irq" },
	{ 0xd272d446, "__fentry__" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xbebe66ff, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0x16ab4215,
	0xe8213e80,
	0xbd03ed67,
	0x5e505530,
	0x7851be11,
	0x7a5ffe84,
	0xd272d446,
	0x0db8d68d,
	0xc87f4bab,
	0x9d33f583,
	0xd272d446,
	0x9c0551c6,
	0xf2f79e52,
	0x9f222e1e,
	0x653aa194,
	0xd5f66efd,
	0x8ea73856,
	0xe486c4b7,
	0x5403c125,
	0xcdec1689,
	0x7f79e79a,
	0x630dad60,
	0x9126ce86,
	0x4e54d6ac,
	0x0bc5fb0d,
	0x1595e410,
	0xa1dacb42,
	0x0571dc46,
	0x9dd4105e,
	0xd272d446,
	0xd272d446,
	0xbebe66ff,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__wake_up\0"
	"_printk\0"
	"__ref_stack_chk_guard\0"
	"kthread_should_stop\0"
	"__SCT__might_resched\0"
	"init_wait_entry\0"
	"schedule\0"
	"prepare_to_wait_event\0"
	"finish_wait\0"
	"kill_fasync\0"
	"__stack_chk_fail\0"
	"__tasklet_schedule\0"
	"fasync_helper\0"
	"alloc_chrdev_region\0"
	"class_create\0"
	"cdev_init\0"
	"cdev_add\0"
	"device_create\0"
	"__init_waitqueue_head\0"
	"tasklet_init\0"
	"kthread_create_on_node\0"
	"wake_up_process\0"
	"request_threaded_irq\0"
	"cdev_del\0"
	"unregister_chrdev_region\0"
	"device_destroy\0"
	"class_destroy\0"
	"kthread_stop\0"
	"free_irq\0"
	"__fentry__\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "040FFCE498C705FA6D8B2D5");
