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
	{ 0xdb760f52, "__kfifo_free" },
	{ 0x274d08dc, "__kfifo_dma_out_prepare" },
	{ 0x89afe34e, "__kfifo_dma_in_prepare" },
	{ 0xc897c382, "sg_init_table" },
	{ 0xf23fcb99, "__kfifo_in" },
	{ 0xc068440e, "__kfifo_alloc" },
	{ 0x50eedeb8, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

