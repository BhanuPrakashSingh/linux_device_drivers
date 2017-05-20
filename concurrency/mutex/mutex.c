#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define FIRST_MINOR 0
#define MINOR_CNT   1
DEFINE_MUTEX(my_mutex);
static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

static int my_open (struct inode *i, struct file *f)
	{
	printk(KERN_INFO "In my open\n"); 
	return 0;
	}

static int my_close (struct inode *i, struct file *f)
	{
	printk(KERN_INFO "In my close\n"); 
	return 0;
	}

//static struct mutex my_mutex;
static char c = 'A';

static ssize_t my_read (struct file *f, char __user *buf, size_t len, loff_t *off)
	{
	printk(KERN_INFO "In my_read\n");
	if(mutex_lock_interruptible(&my_mutex))
		{
		printk(KERN_INFO "unable to aquire mutex\n");
		return -1;
		}
	return 0;
	}

static ssize_t my_write (struct file *f, const char __user *buf, size_t len, loff_t *off)
	{
	printk(KERN_INFO "in my_write\n");
	//release mutex
	mutex_unlock(&my_mutex);
	if(copy_from_user(&c,buf+len-1,1))
		{
		return -EFAULT;
		}
	return len;
	}

static struct file_operations driver_fops =
	{
	.owner = THIS_MODULE,
	.open  = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write,
	};

static int __init init_mutex(void)
	{
	int ret;
	struct device *dev_ret;
	if ((ret=alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "my_mutex")) < 0)
		{
		printk(KERN_ERR "failed to allocate region\n");
		return ret;
		}
	cdev_init(&c_dev, &driver_fops);

	if (ret = cdev_add(&c_dev, dev, MINOR_CNT) < 0)
		{
		printk(KERN_ERR "failed to add device\n");
		unregister_chrdev_region(dev, MINOR_CNT);
		return ret;
		}

	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
		{
		printk(KERN_ERR "failed to create class\n");
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
		}
	if (IS_ERR(dev_ret=device_create(cl, NULL, dev, NULL, "mymutex%d",FIRST_MINOR)))
		{
		printk(KERN_ERR "failed to create a device\n");
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);		
		}
	return 0;
	}

static void __exit exit_mutex(void)
	{
	printk(KERN_INFO "in exit module\n");
	device_destroy(cl,dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	}

module_init(init_mutex);
module_exit(exit_mutex);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bhanu");
MODULE_DESCRIPTION("Binary semaphore semonstration");
