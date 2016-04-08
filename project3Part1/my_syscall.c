#include <linux/syscalls.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <asm/page.h>
#include <asm/pgtable.h>

asmlinkage long long sys_my_syscall(int pid, unsigned long va)
{
	unsigned long long pageFN;
	unsigned long long pa;

	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;
	
	struct mm_struct *mm;

	int found = 0;

	struct task_struct *task;
	for_each_process(task)
	{
		if(task->pid == pid)
			mm = task->mm;
	}
	pgd  = pgd_offset(mm,va);
	if(!pgd_none(*pgd) && !pgd_bad(*pgd))
	{
		pud = pud_offset(pgd,va);
		if(!pud_none(*pud) && !pud_bad(*pud))
		{
			pmd = pmd_offset(pud,va);
			if(!pmd_none(*pmd) && !pmd_bad(*pmd))
			{
				pte = pte_offset_kernel(pmd,va);
				if(!pte_none(*pte))
				{
					pageFN = pte_pfn(*pte);
					pa = ((pageFN<<12)|(va&0x00000FFF));
					found = 1;
					return pa;
				}
			}
		}
	}
	if(pgd_none(*pgd) || pud_none(*pud) || pmd_none(*pmd) || pte_none(*pte))
	{
		unsigned long long swapID = (pte_val(*pte) >> 32);
		found = 1;
		return swapID;
	}
	if(found == 0)
	{
		return 0;
	}	
}

void __exit wip_exit(void)
{
	printk(KERN_ALERT "Removed wip_mod");
}

module_init(wip_init);
module_exit(wip_exit);
MODULE_LICENSE("GPL");
