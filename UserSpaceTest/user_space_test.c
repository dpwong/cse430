#include <linux/unistd.h>
#include <stdio.h>

#define __my_syscall 359

int main()
{
	printf("Running my_syscall\n");
	syscall(__my_syscall);
	return 0;
}