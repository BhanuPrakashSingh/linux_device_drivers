#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT   5
#define MAX	50

static dev_t FIRST_MAJOR;
static struct cdev c_dev;
static struct class *cl;
static int i=0;
//static int ret1=0;
static char kern_buff[50];

static int my_open (struct inode *i, struct file *f)
	{
	printk(KERN_INFO "opening a file frm driver\n"); 
	return 0;
	}

static int my_close (struct inode *i, struct file *f)
	{
	printk(KERN_INFO "closing a file from driver\n"); 
	return 0;
	}


static ssize_t my_read (
struct file *f, char __user *buf, size_t len, loff_t *off)
	{
	printk(KERN_INFO "reading frm driver\n");
	static char kern_buff[50]="my world";
	if(copy_to_user(buf,kern_buff,MAX)!=0)
		return -EFAULT;
	return 0;
	}

static ssize_t my_write (struct file *f, const char __user *buf, size_t len, loff_t *off)
	{
	static char kern_buff[50];
	printk(KERN_INFO "writing from driver\n");
	if(copy_from_user(kern_buff,buf,MAX) != 0)
		return -EFAULT;	
	printk(KERN_INFO "data from user=%s\n",kern_buff);
	return 0;
	}

static struct file_operations driver_fops =
	{
	.owner = THIS_MODULE,
	.open  = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write,
	};

static int __init sem_init(void)
	{
	printk(KERN_INFO "in init module\n");
	int ret;
	struct device *dev_ret;
	if ((ret=alloc_chrdev_region(&FIRST_MAJOR, FIRST_MINOR, MINOR_CNT, "char_dev")) < 0)
		{
		printk(KERN_ERR "failed to allocate region\n");
		return ret;
		}
	cdev_init(&c_dev, &driver_fops);

	if (ret = cdev_add(&c_dev, FIRST_MAJOR, MINOR_CNT) < 0)
		{
		printk(KERN_ERR "failed to add device\n");
		unregister_chrdev_region(FIRST_MAJOR, MINOR_CNT);
		return ret;
		}

	if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
		{
		printk(KERN_ERR "failed to create class\n");
		cdev_del(&c_dev);
		unregister_chrdev_region(FIRST_MAJOR, MINOR_CNT);
		return PTR_ERR(dev_ret);
		}
    
     for(;i<5;i++)
     {
            
//ret1=MKNOD(FIRST_MAJOR,FIRST_MINOR);
	if (IS_ERR(dev_ret=device_create(cl, NULL,MKDEV(MAJOR(FIRST_MAJOR),MINOR(FIRST_MAJOR)+i), NULL, "chardev%d",i)))
		{
		printk(KERN_ERR "failed to create a device\n");
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(FIRST_MAJOR, MINOR_CNT);
		return PTR_ERR(dev_ret);		
		}
     }
	return 0;
	}

static void __exit sem_exit(void)
	{
	printk(KERN_INFO "in exit module\n");
for(i=0;i<5;i++)
     {
	device_destroy(cl,MKDEV(MAJOR(FIRST_MAJOR),MINOR(FIRST_MAJOR)+i));
}
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(FIRST_MAJOR, MINOR_CNT);
	}

module_init(sem_init);
module_exit(sem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manasa");
MODULE_DESCRIPTION("Chardriver acessing five devices");
