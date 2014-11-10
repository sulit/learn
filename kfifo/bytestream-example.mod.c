#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
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
	{ 0xd4733cff, "module_layout" },
	{ 0x4b52ed7c, "noop_llseek" },
	{ 0x4f4dcfda, "remove_proc_entry" },
	{ 0x3943715e, "proc_create_data" },
	{ 0x13d0adf7, "__kfifo_out" },
	{ 0xf23fcb99, "__kfifo_in" },
	{ 0x50eedeb8, "printk" },
	{ 0x4578f528, "__kfifo_to_user" },
	{ 0xcc99e735, "mutex_unlock" },
	{ 0x30a80826, "__kfifo_from_user" },
	{ 0xdd3afd66, "mutex_lock_interruptible" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

