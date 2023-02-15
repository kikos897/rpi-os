#include "arm/sysregs.h"
#include "mm.h"

.section ".text.boot"

.globl _start
_start:

	#bl   delay_ms

	mrs	x0, mpidr_el1
	and	x0, x0, #0x3
	cbz	x0, init_bss
	/* If processor id is not 0 then pending lock processor
	 * (wait for `sev` instruction)
	 */
	wfe
	b	master

proc_hang:
	b 	proc_hang

init_bss:
	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero
	mov	sp,#LOW_MEMORY
	bl	kernel_el3

el3_entry:
	ldr 	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el2,x0

	ldr	x0, =HCR_VALUE
	msr	hcr_el2,x0

	ldr	x0, =SCR_VALUE
	msr	scr_el3,x0

	ldr	x0, =SPSR_VALUE_EL3
	msr	spsr_el3,x0

	adr	x0,el2_entry
	msr	elr_el3,x0
	eret

el2_entry:
	mov	sp, #LOW_MEMORY
	bl	kernel_el2
	
	ldr 	x0, =SCTLR_VALUE_MMU_DISABLED
	msr	sctlr_el1,x0

	ldr	x0, =HCR_VALUE
	msr	hcr_el2,x0

	ldr	x0, =SPSR_VALUE_EL2
	msr	spsr_el2,x0

	adr	x0,el1_entry
	msr	elr_el2,x0
	eret
	
	
el1_entry:
	sev
	mov 	x0, #0
	adr 	x0, coproc_el1

	mov 	x1, #0xe0
	str 	x0, [x1]
	mov 	x1, #0xe8
	str 	x0, [x1]	
	mov 	x1, #0xf0
	str 	x0, [x1]
	
	b master

coproc_el1:
	adr	x0,master
	msr	elr_el3,x0
	eret


master:

	mrs	x0, mpidr_el1
	and	x0, x0, #0x3

	mov	x1, #SECTION_SIZE
	mul	x1, x1, x0
	add	x1, x1, #LOW_MEMORY
	mov	sp, x1

	b	kernel_main

	b 	proc_hang


