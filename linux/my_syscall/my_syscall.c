#include <linux/syscalls.h>

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

asmlinkage long sys_my_syscall(void *buffer)
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

	if (copy_to_user(buffer, (void *)task_list, sizeof(task_list)) > 0)
		printk(KERN_ALERT "Copy to user failed from sys_my_syscall\n");
	else
		printk(KERN_ALERT "Copy to user successful from sys_my_syscall\n");

	return count;
}
