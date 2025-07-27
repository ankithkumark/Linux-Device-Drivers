/*	
 *	File: 		hello_world.c
 *	Details:	Simple hello world driver
 */

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>

//Module init function
static int __init hello_world_init(void){
	printk(KERN_INFO "Module inserted successfully...\n");
	return 0;
}

//Module exit function
static void __exit hello_world_exit(void){
	printk(KERN_INFO "Module removed successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankith Kumar");
MODULE_DESCRIPTION("A simple hello world driver");
MODULE_VERSION("1.0");

