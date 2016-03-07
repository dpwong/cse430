#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/kmod.h>
#include <linux/kthread.h>
#include <linux/signal.h>

#define MAX_NUM_OF_DES 5
#define NUM_OF_TASKS 1024

struct task_struct *new_task;
int data;
int ret;

// recursively returns the number of descendants a parent task has
int count_child_threads(struct task_struct *task)
{
	struct list_head *list;
	struct task_struct *task1 = task;
	int count = 0;
	list_for_each(list, &current->children)
	{	
		task1 = list_entry(list, struct task_struct, sibling);
		count++;
		if(&task1->children != NULL)
		{		
			count += count_child_threads(task1);
		}
	}
	return count;
}
// recursively prints and kills the pid of each descend of task
void kill_tree_pids(struct task_struct *task)
{
	struct list_head *list;
	struct task_struct *task1 = task;
	printk(KERN_ALERT "%d\n", task1->pid);
		list_for_each(list, &current->children)
		{
			task1 = list_entry(list, struct task_struct, sibling);
			if(&task1->children != NULL)
			{
				kill_tree_pids(task1);
			}
			else{
			printk(KERN_ALERT "%d\n", task1->pid);
			send_sig_info(SIGKILL, SEND_SIG_FORCED, task1);
			}
		}
	send_sig_info(SIGKILL, SEND_SIG_FORCED, task);
}

int my_kthread_function(void *data)
{	
	struct task_struct *task;
	int num_of_des;
	while(1)
	{
		msleep(2000);
		for_each_process(task)
		{
			num_of_des = count_child_threads(task);
			if(num_of_des >= MAX_NUM_OF_DES)
			{
				kill_tree_pids(task);
				printk(KERN_ALERT "Fork bomb defused\n");
			}
		}
	}
	return 0;
}
static int __init detector_init(void)
{
	data = 20;
	new_task = kthread_run(my_kthread_function, (void *) &data, "my_kthread");
	return 0;
}

static void __exit detector_exit(void)
{
	ret = kthread_stop(new_task);
	printk(KERN_ALERT "Removed detector\n");
}
module_init(detector_init);
module_exit(detector_exit);
MODULE_LICENSE("GPL");
