#include <linux/unistd.h>
#include <stdio.h>

#define __my_syscall 359

int main(int argc, char *argv[])
{
	if(argc < 2 || argc > 2)
	{
		printf("Usage: ./userSpace <pid> <v_addr>\n");
		return 1;
	}
	else
	{
		unsigned long long ret;
		ret = syscall(__my_syscall, pid, va);
		if((ret >> 63) == 7)
		{
			printf("Physical Address: 0x%08llx",ret);
		}
		else
		{
			if(ret != 0)
				printf("Swap Identifier: 0x%08llx",ret);
			else
				printf("not available");
		}
	}
	return 0;
}

