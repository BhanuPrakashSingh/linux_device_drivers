#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/delay.h>

// Module Licesence 
MODULE_LICENSE("GPL");

static struct task_struct *task;

int thread_function(void *unused)
	{
	//allow the SIGKILL signal
	allow_signal(SIGKILL);
	while (!kthread_should_stop()) {
		printk(KERN_INFO "Thread is running\n");
		ssleep(5);
		//check if signal is pending
		if (signal_pending(task))
			break;
		}
	printk(KERN_INFO "Thread is stopping\n");
	do_exit(0);
	return 0;
	}

static int __init thread_init (void)
	{
	printk(KERN_INFO "Creating thread\n");
	//create a kernel thread with name "mythread"
	task = kthread_run(&thread_function, NULL, "mythread");
	if(task)
		{
		printk(KERN_INFO "Thread created successfully\n");
		//wake_up_process(task);
	} else {
		printk(KERN_INFO "Thread creation failed\n");
	}

	return 0;
	}

//exit module
static void __exit clean_thread(void)
	{
	printk("cleanup thread\n");
	if (task) {
		kthread_stop(task);
		printk(KERN_INFO "Thread stopped\n");
		}
	}

module_init(thread_init);
module_exit(clean_thread);
