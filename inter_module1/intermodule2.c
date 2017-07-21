#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/*GPL License*/
MODULE_LICENSE("GPL");

extern int val_a;
extern int val_b;
extern  int add_mod(int,int);
static int res;

static int hello_init(void)
	{
        res=add_mod(5,2);
	printk(KERN_INFO "sum is=%d\n",res);
	return 0;
	}

static void hello_exit(void)
	{
	printk(KERN_ALERT "Goodbye\n");
	}

module_init(hello_init);
module_exit(hello_exit);
