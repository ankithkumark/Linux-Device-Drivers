/*
 * File:	hello_world.c
 * Details:	A simple hello_world driver for passing arguments.
*/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

int valueETX, arr_valueETX[4];
char *nameETX;
int cb_valueETX = 0;

module_param(valueETX, int, S_IRUSR|S_IWUSR);			//Integer value;
module_param(nameETX, charp, S_IRUSR|S_IWUSR);			//String
module_param_array(arr_valueETX, int, NULL, S_IRUSR|S_IWUSR);	//Array of integer

int notify_param(const char *val, const struct kernel_param *kp){
	int res = param_set_int(val, kp);
	if(res == 0){
		pr_info("Call back function called...\n");
		pr_info("New value of cb_valueETX = %d\n", cb_valueETX);
		return 0;
	}
	return -1;
}

const struct kernel_param_ops my_param_ops = {
	.set = &notify_param,	//Use out setter...
	.get = &param_get_int,	//.. and standard getter
};

module_param_cb(cb_valueETX, &my_param_ops, &cb_valueETX, S_IRUGO|S_IWUSR);

static int __init hello_world_init(void){
	int i;
	pr_info("valueETX = %d\n", valueETX);
	pr_info("cb_valueETX = %d\n", cb_valueETX);
	pr_info("nameETX = %s\n", nameETX);
	for(i=0; i<(sizeof arr_valueETX/sizeof(int)); i++)
		pr_info("arr_valueETX[%d] = %d\n", i, arr_valueETX[i]);
	pr_info("Kernel module inserted succseccfull...\n");
	return 0;
}

static void __exit hello_world_exit(void){
	pr_info("Kernel module removed successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankith Kumar");
MODULE_DESCRIPTION("A simple hello world driver for passing arguments");
MODULE_VERSION("1.0");
