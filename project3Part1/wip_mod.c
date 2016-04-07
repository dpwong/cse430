#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm_types.h>
#include <linux/gup.h>
#include <linux/mm.h>
#include <linux/page.h>
#include <linux/pgtable_32.h>

int __init wip_init(void)
{
	unsigned long long va = 0xb77e5000;
	int pid = 1072;
	struct page p;
	unsigned long long pageFN;
	unsigned long long pa;

	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;

	struct task_struct *task;
	for_each_process(p)
	{
		if(p->pid == pid)
			mm = p->mm;
	}
	pgd  = pgd_offset(mm,va);
	if(!pgd_none(*pgd) || !pgd_bad(*pgd))
	{
		pmd = pmd_offset(pgd,va);
		if(pmd_none(*pmd) || pmd_bad(*pmd))
		{
			pte = pte_offset(pmd,va);
			if(!pte_none(*pte))
			{
				pageFN = pte_pfn(*pte);
				pa = ((pageFN<<12)|(va&0x00000FFF));
				printk(KERN_ALERT "%x%x\n", pa, pageFN);
			}
		}
	}
	
	//unsigned long long pa = p->
}

void __exit wip_exit(void)
{
	printk(KERN_ALERT "Removed wip_mod");
}

module_init(wip_init);
module_exit(wip_exit);
MODULE_LICENSE("GPL");
