#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <asm/pgtable.h>
#include <asm/page.h>

int __init wss_init(void)
{
	int pid = 0;
	int wss = 0;

	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;
	
	struct task_struct *task;
	if(pid->mm != NULL)
	{
	  	for(i=0; i <= PTRS_PER_PGD; i+=8)
	  	{    	pgd = pgd_offset(mm,i);
		   	if(!pgd_none(*pgd) && !pgd_bad(*pgd)
			{
	    			for(j=0; j <= PTRS_PER_PUD; j+=8)
	    			{
					pmd = pmd_offset(pgd,j);
					if(!pmd_none(*pmd) && !pmd_bad(*pmd)
					{
	      					for(k=0; k <= PTRS_PER_PMD; k+=8)
	      					{
							pud = pud_offset(pmd,k);
							if(!pud_none(*pud) && !pud_bad(*pud))
							{
								for(l=0; l <= PTRS_PER_PTE; l+=8)
								{
									pte = pte_offset(pud,l);
									if(pte_young(*pte))
									{
										wss++;
										pte_set(pte, pte_mkold(*pte));
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

void __exit wss_exit(void)
{
	printk(KERN_ALERT "Removed wss");
}

module_init(wss_init);
module_exit(wss_exit);
MODULE_LICENSE("GPL");
