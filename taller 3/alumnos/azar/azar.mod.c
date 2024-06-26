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
	{ 0xf30c37fe, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xb65e5a32, "class_destroy" },
	{ 0x5d9110de, "device_destroy" },
	{ 0xc5850110, "printk" },
	{ 0xdc5df957, "device_create" },
	{ 0x2871e975, "__class_create" },
	{ 0x347a4b9c, "cdev_add" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xcf329118, "cdev_init" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x2276db98, "kstrtoint" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "C9030C57444F76E02E6615E");
