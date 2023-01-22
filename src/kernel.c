#include "pl011_uart.h"
#include "utils.h"

void kernel_main(unsigned long processor_index)
{
	static unsigned int current_processor_index = 0;

	if (processor_index == 0) 
	{
		pl011_uart_init();
		pl011_uart_send_string("\r\nInit UART4 PL011 ");
	}

	while (processor_index != current_processor_index)
	{
		delay(50);
	}

	pl011_uart_send_string("\r\n");
	pl011_uart_send_string("Hello du processor ");
	pl011_uart_send_int(processor_index);
	pl011_uart_send_string("!\r\n");

	current_processor_index++;

	// if current_processor_index == 4 then all processors send message
	while (current_processor_index != 3);
	while(1) 
	{
		char r =pl011_uart_recv();
		if(r=='\n' || r=='\r') pl011_uart_send_string("\r\n");
		else pl011_uart_send(r);
	}
}
