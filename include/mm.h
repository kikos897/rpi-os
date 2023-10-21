#ifndef	_MM_H
#define	_MM_H

#include "peripherals/base.h"

#define PAGE_SHIFT	 		12
#define TABLE_SHIFT 			9
#define SECTION_SHIFT			(PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE   			(1 << PAGE_SHIFT)	
#define SECTION_SIZE			(1 << SECTION_SHIFT)	

#define LOW_MEMORY              	(2 * SECTION_SIZE)
#define MALLOC_START			0x40000000
#define HIGH_MEMORY			0xFC000000

#define PAGING_MEMORY			(HIGH_MEMORY - MALLOC_START)
#define PAGING_PAGES			(PAGING_MEMORY/PAGE_SIZE)


#ifndef __ASSEMBLER__

#include "types.h"

void memzero(unsigned long src, unsigned long n);
u64 get_free_page();
void free_page(unsigned long p);
#endif

#endif  /*_MM_H */
