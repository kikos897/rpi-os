#ifndef _SYSREGS_H
#define _SYSREGS_H

// ***************************************
// SCTLR_EL1, System Control Register (EL1), Page 2654 of AArch64-Reference-Manual.
// ***************************************
#define SCTLR_RESERVED			(3<<28)|(3<<22)|(1<<20)|(1<<11) //RESERVED BITS SHOULD BE INIT AT 1
#define SCTLR_EE_LITTLE_ENDIAN		(0<<25)				//LITTLE ENDIAN FOR EL1
#define SCTLR_EOE_LITTLE_ENDIAN		(0<<24)				//LITTLE ENDIAN FOR EL0
#define SCTLR_I_CACHE_DISABLE		(0<<12)				//DISABLE INSTRUCTION CACHE
#define SCTLR_D_CACHE_DISABLE		(0<<2)				//DISABLE DATA CACHE
#define SCTLR_MMU_DISABLE		(0<<0)				//DISABLE MMU
#define SCTLR_VALUE_MMU_DISABLED	(SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN | SCTLR_EOE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLE | SCTLR_D_CACHE_DISABLE | SCTLR_MMU_DISABLE )

// ***************************************
// HCR_EL2, Hypervisor Configuration Register (EL2), Page 2487 of AArch64-Reference-Manual.
// ***************************************
#define	HCR_RW				(1<<31)				//ENABLE ARCH64 AT EL1
#define	HCR_VALUE			(HCR_RW)			//SET THE HCR VALUE

// ***************************************
// SCR_EL3, Secure Configuration Register (EL3), Page 2648 of AArch64-Reference-Manual.
// ***************************************
#define	SCR_RESERVED			(3<<4)				//RESERVED BITS SHOULD INIT AT 1
#define	SCR_RW				(1<<10)				//ENABLE AARCH64 FOR EL2
#define SCR_NS				(1<<0)				//NS BIT EL0 AND EL1 ARE IN NONE SECURE STATE
#define SCR_VALUE			(SCR_RESERVED | SCR_RW | SCR_NS)//SET THE SCR VALUE

// ***************************************
// SPSR_EL3, Saved Program Status Register (EL3) Page 389 of AArch64-Reference-Manual.
// ***************************************
#define	SPSR_MASK_ALL			(7<<6)				//ALL INTERRUPTS WILL BE DISABLED
#define	SPSR_EL1H			(5<<0)				//WE USE EL1H THAT HAS DEDICATED STACK POINTER
#define	SPSR_VALUE			(SPSR_MASK_ALL | SPSR_EL1H)	//SET THE SPSR VALUE

#endif
