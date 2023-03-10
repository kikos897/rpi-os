#include "pl011_uart.h"
#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "irq.h"

void putc(void *p, char c)
{

	pl011_uart_send(c);
}

void kernel_el3()
{
	pl011_uart_init();
	init_printf(0,putc);
	printf("\r\nInit UART4 PL011 ");
	printf("\r\nRunning at level EL%d\r\n",get_el());
	
	irq_vector_init();
	enable_interrupt_controller();
	enable_irq();
	timer_init();


}

void kernel_el2()
{
	printf("\r\nRunning at level EL%d",get_el());
}

void kernel_main(unsigned long processor_index)
{
	static unsigned int current_processor_index = 0;

	printf("\r\nRunning at level EL%d",get_el());

	while (processor_index != current_processor_index)
	{
		delay(50);
	}

	printf("\r\nHello du processor %d\r\n",processor_index);

	//current_processor_index++;

	// if current_processor_index == 4 then all processors send message
	//while (current_processor_index != 3);

	while(1) 
	{
		char r =pl011_uart_recv();
		if(r=='\n' || r=='\r') printf("\r\n");
		else printf("%c",r);
		
	}
}
