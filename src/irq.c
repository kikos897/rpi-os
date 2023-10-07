#include "utils.h"
#include "printf.h"
#include "peripherals/irq.h"
#include "irq.h"
#include "timer.h"
#include "mini_uart.h"
#include "peripherals/mini_uart.h"

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
	put32(IRQ0_SET_EN_0,AUX_IRQ | SYSTEM_TIMER_IRQ_1);

}

void handle_irq()
{
	unsigned int irq = get32(IRQ0_PENDING_0);
	while(irq)
	{
		if(irq & SYSTEM_TIMER_IRQ_1)
		{
			irq&=~SYSTEM_TIMER_IRQ_1;
			handle_timer_irq();
		}
		else if (irq & AUX_IRQ)
		{
			irq&=~AUX_IRQ;
			while((get32(AUX_MU_IIR_REG) & 4)==4)
			{
				char r=uart_recv();
				if(r=='\n' || r=='\r') printf("\r\n");
				else printf("%c",r);
			}
		}
		else	printf("Unknown pending irq: %x\r\n",irq);
	}
}
