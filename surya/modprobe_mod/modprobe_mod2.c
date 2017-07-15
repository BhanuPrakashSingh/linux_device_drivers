#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

/* GPL License*/
MODULE_LICENSE("GPL");

static void display(int num, char* string)
	{
	printk("num=%d\nstring=%s\n",num,string);
	}

EXPORT_SYMBOL(display);

static int __init display_mod_init(void)
	{
	printk(KERN_INFO "in modprobe_mod2 init\n");
	return 0;
	}

static void __exit display_mod_exit(void)
	{
	printk(KERN_INFO "Exiting from module2\n");
	}

module_init(display_mod_init);
module_exit(display_mod_exit);
