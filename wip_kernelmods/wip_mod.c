#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/string.h>

int __init wip_init(void)
{
	struct thread_info *threadinfo;
	struct task_struct *tasks;
	char comm[TASK_COMM_LEN];

	printk(KERN_ALERT "Inserted wip_mod\n");

	// get current tasks
	threadinfo = current_thread_info();
	tasks = threadinfo->task;

	// probably init?
	strcpy(comm, tasks->comm);

	printk(KERN_ALERT "task name --> %s\n", comm);

	return 0;
}

void __exit wip_exit(void)
{
	printk(KERN_ALERT "Removed wip_mod\n");
}

module_init(wip_init);
module_exit(wip_exit);
MODULE_LICENSE("GPL");