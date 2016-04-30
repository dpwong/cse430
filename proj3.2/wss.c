#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/pagemap.h>
#include <linux/delay.h>
#include <linux/highmem.h>

#include <linux/kthread.h>

struct task_struct *kthread;

int kthread_wss(void *data)
{
	unsigned long va;
	int ret;
	int wss;

	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *ptep;
	
	struct task_struct *task;
	while(!kthread_should_stop())
	{
		printk(KERN_INFO "Checking process' WSS.\n");
		for_each_process(task)
		{
			wss = 0;
			if(task->mm != NULL)
			{
				struct vm_area_struct *temp = task->mm->mmap;
				while(temp)
				{
					if(temp->vm_flags & VM_IO){}
					else
					{
						for(va = temp->vm_start; va < temp->vm_end; va+=PAGE_SIZE)
						{
				  			pgd = pgd_offset(task->mm,va);
			 		  		if(pgd_none(*pgd))
								break;
							pud = pud_offset(pgd,va);
							if(pud_none(*pud))
								break;
							pmd = pmd_offset(pud,va);
							if(pmd_none(*pmd))
								break;
							ptep = pte_offset_map(pmd,va);
							ret = 0;
							if(pte_young(*ptep))
							{
								ret = test_and_clear_bit(_PAGE_BIT_ACCESSED,												(unsigned long *) &ptep->pte);
								wss++;
							}
							if(ret)
							{
								pte_update(task->mm, va, ptep);
							}
							pte_unmap(ptep);
						}
					}
					temp = temp->vm_next;
				}
				printk(KERN_INFO "%i: %i\n", task->pid, wss);
			}
		}
	msleep(1000);
	}
	return 0;
}

static int __init wss_init(void)
{
	int data = 20;
	kthread = kthread_run(&kthread_wss, (void*)data, "kthread_wss");
	return 0;
}
static void __exit wss_exit(void)
{
	kthread_stop(kthread);
	printk(KERN_ALERT "Removed wss\n");
}

module_init(wss_init);
module_exit(wss_exit);
MODULE_LICENSE("GPL");
