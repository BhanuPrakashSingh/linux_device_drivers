#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include<linux/semaphore.h>
#include<linux/signal.h>
#include<linux/sched.h>


static struct semaphore my_sem;
static int a=57;

static struct task_struct *task1;
static struct task_struct *task2;

 //Function executed by kernel thread
static int thread_fn1(void *unused)
{
//Allow SIGKILL
allow_signal(SIGKILL);
printk(KERN_INFO "in thread_fun1\n");
while(!kthread_should_stop())
{
printk(KERN_INFO "1 aquiring lock\n");
if(down_interruptible(&my_sem))
		{
		printk(KERN_INFO "unable to aquire semaphore\n");
		return -1;
		}
a+=5;
printk("after incrementing in hanlr_1 a=%d\n",a);
up(&my_sem);
// Check if the signal is pending
       // if (signal_pending(task1))
         //   break;
}
printk(KERN_INFO "Stopping thread\n");
do_exit(0);
return 0;
}


static int thread_fn2(void *unused)
{
//Allow SIGKILL
allow_signal(SIGKILL);
printk("in handler function 2");
while(!kthread_should_stop())
{
printk(KERN_INFO "2 aquiring lock\n");
if(down_interruptible(&my_sem))
                {
                printk(KERN_INFO "unable to aquire semaphore\n");
                return -1;
                }
a-=5;
printk("after decrementing in hanlr_2 a=%d\n",a);
up(&my_sem);
// Check if the signal is pending
       // if (signal_pending(task2))
         //   break;  
}
printk(KERN_INFO "Stopping thread\n");
do_exit(0);
return 0;
}

// Module Initialization
static int __init init_thread(void)
{
sema_init(&my_sem,1);
    printk(KERN_INFO "Creating Thread\n");
    //Create the kernel thread with name 'mythread'
    task1 = kthread_run(thread_fn1, NULL, "mythread1");
    task2= kthread_run(thread_fn2, NULL, "mythread2");
	printk(KERN_INFO"a=%d\n",a);
    if (task1 && task2)
        printk(KERN_INFO "Thread Created successfully\n");
    else
        printk(KERN_ERR "Thread creation failed\n");

    return 0;
}
// Module Exit
static void __exit cleanup_thread(void)
{
   printk(KERN_INFO "Cleaning Up\n");
   if (task1)
   {
	printk(KERN_INFO "in exit module, stoping thread1\n");
	kthread_stop(task1);
}
if(task2) {
	printk(KERN_INFO "in exit module, stoping thread2\n");
	kthread_stop(task2);
   }
       printk(KERN_INFO "Thread stopped");
}
MODULE_LICENSE("GPL");
MODULE_AUTHOR("	manasa&pragna");
module_init(init_thread);
module_exit(cleanup_thread);

