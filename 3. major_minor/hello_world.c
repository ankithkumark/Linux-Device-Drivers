/*
 * File:	hello_world.c
 * Details:	Simple linux driver to allocate major and minor number statically
*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>

dev_t dev = MKDEV(235, 0);

static int __init hello_world_init(void){
	register_chrdev_region(dev, 1, "mouse_potato_dev");
	pr_info("Major = %d Minor = %d\n", MAJOR(dev), MINOR(dev));
	pr_info("Kernel module inserted successfully...\n");
	return 0;
}

static void __exit hello_world_exit(void){
	unregister_chrdev_region(dev, 1);
	pr_info("Kernel module removed successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankith Kumar");
MODULE_DESCRIPTION("Simple linux driver to allocate major and minor number");
MODULE_VERSION("1.0");
