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

void printTask(int pid, char *tty_name, unsigned long time_seconds, char *comm)
{
	int hours;
	int minutes;
	char hoursStr[3];
	char minutesStr[3];
	char secondsStr[3];

	hours = time_seconds / 3600;
	time_seconds -= hours * 3600;

	// time_seconds now holds seconds, but strictly less than one hour
	minutes = time_seconds / 60;
	time_seconds -= minutes * 60;
	
	// time_seconds now holds seconds, but strictly less than one minute

	if (hours >= 10)
		sprintf(hoursStr, "%d", hours);
	else
		sprintf(hoursStr, "0%d", hours);

	if (minutes >= 10)
		sprintf(minutesStr, "%d", minutes);
	else
		sprintf(minutesStr, "0%d", minutes);

	if (time_seconds >= 10)
		sprintf(secondsStr, "%lu", time_seconds);
	else
		sprintf(secondsStr, "0%lu", time_seconds);

	printf("%d\t%s\t%s:%s:%s\t%s\n", pid, tty_name, hoursStr, minutesStr, secondsStr, comm);
}

int main()
{
	struct task_info tasks[NUM_OF_TASKS];
	int ret = 0;
	int i;

	ret = syscall(__my_syscall, tasks);

	printf("PID\tTTY\tTIME\tCMD\n");

	for (i = 0; i < ret; i++)
	{
		printTask(tasks[i].pid, tasks[i].tty_name, tasks[i].time_seconds, tasks[i].comm);
	}
	return 0;
}