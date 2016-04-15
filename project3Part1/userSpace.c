#include <linux/unistd.h>
#include <stdio.h>

#define __my_syscall 359

int main(int argc, char *argv[])
{
	if(argc < 3 || argc > 3)
	{
		printf("Usage: ./userSpace <pid> <v_addr>\n");
		return 1;
	}
	else
	{
		int pid = atoi(argv[1]);
		unsigned long long va = strtoull(argv[2],NULL,16);
		unsigned long long ret;
		ret = syscall(__my_syscall, pid, va);
		printf("0x%08llx\n",ret);
		/*if((ret >> 60) == 7)
		{
			printf("Physical Address: 0x%08llx\n",ret);
		}
		else
		{
			if(ret != 0)
				printf("Swap Identifier: 0x%08llx\n",ret);
			else
				printf("not available\n");
		}*/
	}
	return 0;
}

