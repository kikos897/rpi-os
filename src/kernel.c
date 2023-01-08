#include "mini_uart.h"
#include "utils.h"

void kernel_main(unsigned long processor_index)
{
	static unsigned int current_processor_index = 0;

	if (processor_index == 0) 
	{
		uart_init();
		uart_send_string("\r\nInit UART ");
	}

	while (processor_index != current_processor_index)
	{
		delay(50);
	}

	uart_send_string("\r\n");
	uart_send_string("Hello du processor ");
	uart_send_int(processor_index);
	uart_send_string("!\r\n");

	current_processor_index++;

	// if current_processor_index == 4 then all processors send message
	while (current_processor_index != 3);
	while(1) 
	{
		char r =uart_recv();
		if(r=='\n' || r=='\r') uart_send_string("\r\n");
		else uart_send(r);
	}
}
