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

static int __init twss_init(void)
{
	int twss = 0;
	unsigned long va;
	int ret;
	int wss;

	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *ptep;
	
	struct task_struct *task;
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
							return -1;
						pud = pud_offset(pgd,va);
						if(pud_none(*pud))
							return -1;
						pmd = pmd_offset(pud,va);
						if(pmd_none(*pmd))
							return -1;
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
		}
		twss += wss;
	}
	printk(KERN_ALERT "Total WSS: %i\n",twss);
	if(twss > 464225)
		printk(KERN_ALERT "Kernel Alert!");
	
	return 0;
}

static void __exit twss_exit(void)
{
	printk(KERN_ALERT "Removed twss");
}

module_init(twss_init);
module_exit(twss_exit);
MODULE_LICENSE("GPL");
