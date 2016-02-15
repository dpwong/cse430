#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/tty.h>

#define NUM_OF_TASKS 1024

struct task_info {
	int pid;
	char comm[TASK_COMM_LEN];
	char tty_name[64];
	unsigned long time_seconds;
};

int __init wip_init(void)
{
	struct task_info task_list[NUM_OF_TASKS];
	struct task_struct *task;
	int count = 0;
	int i;
	char no_tty[2];

	no_tty[0] = '?';
	no_tty[1] = '\0';

	task = current;

	for_each_process(task)
	{
		strcpy(task_list[count].comm, task->comm);
		task_list[count].pid = task->pid;
		task_list[count].time_seconds = (cputime_to_jiffies(task->stime) + cputime_to_jiffies(task->utime)) / HZ;

		if (task->signal->tty != NULL)
		{
			strcpy(task_list[count].tty_name, task->signal->tty->name);
		}
		else
			strcpy(task_list[count].tty_name, no_tty);
		count++;
	}
	task = NULL;

	// print all processes
	for (i = 0; i < count; i++)
	{
		printk(KERN_ALERT "%d %s %s %lu\n", task_list[i].pid, task_list[i].comm, task_list[i].tty_name, task_list[i].time_seconds);
	}

	printk(KERN_ALERT "sizeof(task_list) = %u\n", sizeof(task_list));
	return 0;
}

void __exit wip_exit(void)
{
	printk(KERN_ALERT "Removed wip_mod\n");
}

module_init(wip_init);
module_exit(wip_exit);
MODULE_LICENSE("GPL");