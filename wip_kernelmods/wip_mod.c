#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

int __init wip_init(void)
{
	printk(KERN_ALERT "Inserted wip_mod\n");
	return 0;
}

void __exit wip_exit(void)
{
	printk(KERN_ALERT "Removed wip_mod\n");
}

module_init(wip_init);
module_exit(wip_exit);
MODULE_LICENSE("GPL");