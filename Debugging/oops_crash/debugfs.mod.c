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
	{ 0x74fc8c8a, "debugfs_remove" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x357aaab3, "mutex_lock_interruptible" },
	{ 0x058c185a, "jiffies" },
	{ 0x40a621c5, "snprintf" },
	{ 0xf46d5bf3, "mutex_unlock" },
	{ 0x9479a1e8, "strnlen" },
	{ 0x437e81c7, "simple_read_from_buffer" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xe54e0a6b, "__fortify_panic" },
	{ 0x2379af1d, "debugfs_create_dir" },
	{ 0xbd03ed67, "random_kmalloc_seed" },
	{ 0x08bfc903, "kmalloc_caches" },
	{ 0xecd17989, "__kmalloc_cache_noprof" },
	{ 0x6d2a89ad, "debugfs_create_file_full" },
	{ 0xcec7a145, "debugfs_create_u32" },
	{ 0x23f25c0a, "__dynamic_pr_debug" },
	{ 0x4d8419c6, "param_ops_int" },
	{ 0xd272d446, "__fentry__" },
	{ 0xcb8b6ec6, "kfree" },
	{ 0xe8213e80, "_printk" },
	{ 0x814e12e5, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xd272d446,
	0x74fc8c8a,
	0xbd03ed67,
	0x357aaab3,
	0x058c185a,
	0x40a621c5,
	0xf46d5bf3,
	0x9479a1e8,
	0x437e81c7,
	0xd272d446,
	0xe54e0a6b,
	0x2379af1d,
	0xbd03ed67,
	0x08bfc903,
	0xecd17989,
	0x6d2a89ad,
	0xcec7a145,
	0x23f25c0a,
	0x4d8419c6,
	0xd272d446,
	0xcb8b6ec6,
	0xe8213e80,
	0x814e12e5,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"__x86_return_thunk\0"
	"debugfs_remove\0"
	"__ref_stack_chk_guard\0"
	"mutex_lock_interruptible\0"
	"jiffies\0"
	"snprintf\0"
	"mutex_unlock\0"
	"strnlen\0"
	"simple_read_from_buffer\0"
	"__stack_chk_fail\0"
	"__fortify_panic\0"
	"debugfs_create_dir\0"
	"random_kmalloc_seed\0"
	"kmalloc_caches\0"
	"__kmalloc_cache_noprof\0"
	"debugfs_create_file_full\0"
	"debugfs_create_u32\0"
	"__dynamic_pr_debug\0"
	"param_ops_int\0"
	"__fentry__\0"
	"kfree\0"
	"_printk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9A047A59650B323364D40A1");
