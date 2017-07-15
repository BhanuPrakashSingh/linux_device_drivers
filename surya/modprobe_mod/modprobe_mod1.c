#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

/* GPL License*/
MODULE_LICENSE("GPL");

int num;
char* string;
extern void display(int,char*);
module_param(num,int,0644);
module_param(string,charp,0644);

static int __init cmd_mod_i(void)
	{
	printk(KERN_INFO "in module 1\n");
	display(num,string);
	return 0;
	}

static void __exit cmd_mod_e(void)
	{
	printk(KERN_INFO "Exiting from module1\n");
	}

module_init(cmd_mod_i);
module_exit(cmd_mod_e);
