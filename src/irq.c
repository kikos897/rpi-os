#include "utils.h"
#include "printf.h"
#include "peripherals/irq.h"
#include "irq.h"
#include "timer.h"

void show_invalid_entry_message(int type,int esr,int elr)
{
	printf("Unkown ERROR type:%d, ESR:%d, ELR:%d\r\n",type,esr,elr);	
}

void enable_interrupt_controller()
{
	put32(IRQ0_SET_EN_0,SYSTEM_TIMER_IRQ_1);
}

void handle_irq()
{
	unsigned int irq = get32(IRQ0_PENDING_0);
	switch(irq)
	{
		case(SYSTEM_TIMER_IRQ_1):
			handle_timer_irq();
		break;
		default:
			printf("Unknown pending irq: %x\r\n",irq);

	}
}
