#include <linux/unistd.h>
#include <stdio.h>

#define __my_syscall 359
#define TASK_COMM_LEN 16
#define NUM_OF_TASKS 1024

struct task_info {
	int pid;
	char comm[TASK_COMM_LEN];
	char tty_name[64];
	unsigned long time_seconds;
};

int main()
{
	struct task_info tasks[NUM_OF_TASKS];
	int ret = 0;
	int i;

	printf("Running my_syscall\n");
	ret = syscall(__my_syscall, tasks);
	printf("returned: %d\n", ret);

	printf("PID\tTTY\tTIME\tCMD\n");

	for (i = 0; i < ret; i++)
	{
		printf("%d\t%s\t%lu\t%s\n", tasks[i].pid, tasks[i].tty_name, tasks[i].time_seconds, tasks[i].comm);
	}
	return 0;
}