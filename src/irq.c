#include "utils.h"
#include "printf.h"
#include "peripherals/irq.h"
#include "irq.h"
#include "timer.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",
	"FIQ_INVALID_EL1t",
	"ERROR_INVALID_EL1T",

	"SYNC_INVALID_EL1h",
	"IRQ_INVALID_EL1h",
	"FIQ_INVALID_EL1h",
	"ERROR_INVALID_EL1h",

	"SYNC_INVALID_EL0_64",
	"IRQ_INVALID_EL0_64",
	"FIQ_INVALID_EL0_64",
	"ERROR_INVALID_EL0_64",

	"SYNC_INVALID_EL0_32",
	"IRQ_INVALID_EL0_32",
	"FIQ_INVALID_EL0_32",
	"ERROR_INVALID_EL0_32"
};


void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	printf("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}


void enable_interrupt_controller()
{
	//printf("\r\nlaaaaaaaa Controller\r\n");
	put32(IRQ0_SET_EN_0,SYSTEM_TIMER_IRQ_1);
	//printf("\r\n EN0:%x , TIMER1: %x  \r\n",IRQ0_SET_EN_1,SYSTEM_TIMER_IRQ_1);
	//printf("\r\n PENDING 0: %x  \r\n",(get32(IRQ0_PENDING_0)));
}

void handle_irq()
{
	unsigned int irq = get32(IRQ0_PENDING_0);
	//printf("\r\nlaaaaaaaa A\r\n");
	while(irq)
	{
		if(irq & SYSTEM_TIMER_IRQ_1)
		{
			//printf("\r\nlaaaaaaaa B\r\n");
			irq&=~SYSTEM_TIMER_IRQ_2;
			handle_timer_irq();
		}
		
		else	printf("Unknown pending irq: %x\r\n",irq);

	}
}
