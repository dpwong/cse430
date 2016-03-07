#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/kmod.h>
#include <linux/kthread.h>
#include <linux/signal.h>
#include <linux/string.h>
#include <linux/uidgid.h>

#define MAX_NUM_OF_DES 20
#define NUM_OF_TASKS 1024

struct task_struct *new_task;
int data;
int ret;

// recursively returns the number of descendants a parent task has
int count_child_threads(struct task_struct *task)
{
	struct task_struct *task1;
	int count = 0;
	for_each_process(task1)
	{
		if(task1->pid > 100 && gid_eq(task1->cred->gid, task->cred->gid) && (task1->pid - task->pid) < 21)
			count ++;
	}
	return count;
}
// recursively prints and kills the pid of each descend of task
void kill_tree_pids(struct task_struct *task)
{
	struct task_struct *task1;
	kgid_t gid1 = task->cred->gid;
	for_each_process(task1)
	{
		if(gid_eq(gid1, task1->cred->gid))
		{
			printk(KERN_ALERT "%d\n", task1->pid);
			send_sig_info(SIGKILL, SEND_SIG_FORCED, task1);
		}
	}
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
