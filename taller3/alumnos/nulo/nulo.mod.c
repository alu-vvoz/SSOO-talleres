#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
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
__used __section(__versions) = {
	{ 0xa29da427, "module_layout" },
	{ 0xb65e5a32, "class_destroy" },
	{ 0x5d9110de, "device_destroy" },
	{ 0xf30c37fe, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xdc5df957, "device_create" },
	{ 0x2871e975, "__class_create" },
	{ 0x347a4b9c, "cdev_add" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xcf329118, "cdev_init" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "49D36133EDB6568DABBAA2E");
