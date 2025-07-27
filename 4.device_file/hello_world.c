/*
 * File: 	hello_world.c
 * Details:	Simple linux driver to create device file automatically
*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/err.h>
#include<linux/device.h>
#include<linux/err.h>

dev_t dev = 0;
static struct class *dev_class;

static int __init hello_world_init(void){
	if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) < 0){
		pr_err("Cannot allocate major number for device\n");
		return -1;
	}
	pr_info("Major = %d Minor = %d\n", MAJOR(dev), MINOR(dev));

	dev_class = class_create("etx_class");
	if(IS_ERR(dev_class)){
		pr_err("Cannot create the struct class for device\n");
		goto r_class;
	}
	if(IS_ERR(device_create(dev_class, NULL, dev, NULL, "etx_device"))){
		pr_err("Cannot create the device\n");
		goto r_device;
	}
	pr_info("Kernel module inserted successfully...\n");
	return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev, 1);
	return -1;
}

static void __exit hello_world_exit(void){
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, 1);
	pr_info("Kernel module removed successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankith Kumar");
MODULE_DESCRIPTION("A simple linux driver to create device file automatically");
MODULE_VERSION("1.0");
