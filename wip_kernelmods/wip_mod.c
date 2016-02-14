#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/string.h>
#include <linux/slab.h>

struct task_info {
	pid_t pid;
	// cputime_t stime;
	char comm[TASK_COMM_LEN];
	// struct signal_struct *signal;
};

int __init wip_init(void)
{
	struct task_info **task_list;
	struct task_info *new_task;
	struct task_info temp_task;
	struct task_struct *task;
	
	unsigned int count = 0;
	int i = 0;
	printk(KERN_ALERT "Inserted wip_mod\n");

	task = current;
	for_each_process(task)
	{
		count++;
	}

	task_list = (struct task_info **)kmalloc(count * sizeof(struct task_info), GFP_KERNEL);


	for_each_process(task)
	{
		new_task = (struct task_info *)kmalloc(sizeof(struct task_info), GFP_KERNEL);
		strcpy(new_task->comm, task->comm);
		task_list[i] = new_task;
		kfree(new_task);
		i++;
	}
	task = NULL;

	// Now that everything is in the array,
	// it's time to print the last one to check
	printk(KERN_ALERT "There were %u processes\n", count);
	temp_task = *(task_list[count - 1]);
	printk(KERN_ALERT "The last process was %s\n", temp_task.comm);

	return 0;
}

void __exit wip_exit(void)
{
	printk(KERN_ALERT "Removed wip_mod\n");
}

module_init(wip_init);
module_exit(wip_exit);
MODULE_LICENSE("GPL");