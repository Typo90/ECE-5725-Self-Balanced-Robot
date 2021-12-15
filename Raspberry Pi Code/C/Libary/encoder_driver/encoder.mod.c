#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
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
__used
__attribute__((section("__versions"))) = {
	{ 0xf230cadf, "module_layout" },
	{ 0xd64795cd, "class_destroy" },
	{ 0x8c76ee53, "cdev_del" },
	{ 0x17ae16c5, "device_destroy" },
	{ 0xfe990052, "gpio_free" },
	{ 0xc1514a3b, "free_irq" },
	{ 0x37a0cba, "kfree" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0xfcec0987, "enable_irq" },
	{ 0xc04ebd1, "gpiod_to_irq" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x403f9529, "gpio_request_one" },
	{ 0xabe5f4f7, "device_create" },
	{ 0x89ab7bf8, "cdev_add" },
	{ 0x2b68ed92, "cdev_init" },
	{ 0x4751a8ae, "__class_create" },
	{ 0x1e9a78cc, "kmem_cache_alloc_trace" },
	{ 0x51201dd7, "kmalloc_caches" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xca54fee, "_test_and_set_bit" },
	{ 0xf4fa543b, "arm_copy_to_user" },
	{ 0x7c32d0f0, "printk" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x924948ef, "gpiod_get_raw_value" },
	{ 0xe851e37e, "gpio_to_desc" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B269D1C0BD0B2088FF2CDAB");
