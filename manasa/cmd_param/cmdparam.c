#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
/*GPL License*/
MODULE_LICENSE("GPL");
static int cmdParam;
static char *cmdchar;
module_param(cmdParam,int,0644);
module_param(cmdchar,charp,0644);


static int param_init(void)
	{
	printk(KERN_INFO "cmd line parameter val=%d\n",cmdParam);
	printk(KERN_INFO "cmd line string val=%s\n",cmdchar);
	return 0;
	}

static void param_exit(void)
	{
	printk(KERN_ALERT "Goodbye\n");
	}

module_init(param_init);
module_exit(param_exit);

