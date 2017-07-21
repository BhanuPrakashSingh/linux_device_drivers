#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x959613cc, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xd368f9e, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xeab1b17b, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xf3d51bba, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x952664c5, __VMLINUX_SYMBOL_STR(do_exit) },
	{ 0xf22449ae, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x71e3cecb, __VMLINUX_SYMBOL_STR(up) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x6df1aaf1, __VMLINUX_SYMBOL_STR(kernel_sigaction) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "07C1FBF8F08B11546F98594");
