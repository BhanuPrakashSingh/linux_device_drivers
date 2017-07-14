#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*GPL License*/
MODULE_LICENSE("GPL");



static int add_mod( int val_a,int val_b)
{
return val_a+val_b;
}


EXPORT_SYMBOL_GPL(add_mod);

static int hello_init(void)
	{
	printk("Welcome to Module1\n");
	return 0;
	}

static void hello_exit(void)
	{
	printk(KERN_ALERT "Goodbye\n");
	}

module_init(hello_init);
module_exit(hello_exit);


