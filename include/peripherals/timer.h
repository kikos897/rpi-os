#ifndef	_P_TIMER_H
#define	_P_TIMER_H

#include "peripherals/base.h"

#define IRQ_BASE		(PBASE + 0x00003000)

#define	SYSTEM_TIMER_CS		(IRQ_BASE + 0x00)
#define	SYSTEM_TIMER_CLO	(IRQ_BASE + 0x04)
#define	SYSTEM_TIMER_CHI	(IRQ_BASE + 0x08)
#define	SYSTEM_TIMER_C0		(IRQ_BASE + 0x0c)
#define SYSTEM_TIMER_C1		(IRQ_BASE + 0x10)
#define	SYSTEM_TIMER_C2		(IRQ_BASE + 0x14)
#define	SYSTEM_TIMER_C3		(IRQ_BASE + 0x18)

#define TIMER_CS_M0		(1<<0)
#define TIMER_CS_M1		(1<<1)
#define TIMER_CS_M2		(1<<2)
#define TIMER_CS_M3		(1<<3)

#endif	/*_P_TIMER_H */
