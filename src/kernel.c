#include "mini_uart.h"
#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "irq.h"

void putc(void *p, char c)
{

	uart_send(c);
}

void kernel_el3()
{
	uart_init();
	init_printf(0,putc);
	printf("\r\nInit UART4 PL011 ");
	printf("\r\nRunning at level EL%d\r\n",get_el());
	delay(500);	
	
}

void kernel_el2()
{
	printf("\r\nRunning at level EL%d",get_el());
	delay(500);
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

	timer_init();
	irq_vector_init();
	enable_interrupt_controller();
	enable_irq();


	while(1) 
	{

	}
}
