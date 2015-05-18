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
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xe2d5255a, "strcmp" },
	{ 0xaa6901ac, "__kfifo_out_r" },
	{ 0xbee90f2f, "__kfifo_out_peek_r" },
	{ 0x93215e1d, "__kfifo_skip_r" },
	{ 0x37f614b7, "__kfifo_len_r" },
	{ 0x2ec524ad, "__kfifo_in_r" },
	{ 0x50eedeb8, "printk" },
	{ 0xa6970398, "__kfifo_to_user_r" },
	{ 0xcc99e735, "mutex_unlock" },
	{ 0x26bb950b, "__kfifo_from_user_r" },
	{ 0xdd3afd66, "mutex_lock_interruptible" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

