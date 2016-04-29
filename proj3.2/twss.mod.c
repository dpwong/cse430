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
	{ 0xf922ce58, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x4d9e4938, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x22da4565, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xccd30a83, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x4fca9dfe, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0x74a436c4, __VMLINUX_SYMBOL_STR(mem_section) },
	{ 0x39d5bdc1, __VMLINUX_SYMBOL_STR(pv_mmu_ops) },
	{ 0xb1ea840, __VMLINUX_SYMBOL_STR(init_task) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7C5075377E1050ABE64373F");
