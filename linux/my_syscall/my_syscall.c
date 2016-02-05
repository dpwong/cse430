#include <linux/syscalls.h>

asmlinkage void sys_my_syscall(void)
{
	printk(KERN_ALERT "This is the new system call Ahanuf Hossain implemeted.\n");
}
