#include "mini_uart.h"
#include "utils.h"
#include "printf.h"
#include "timer.h"
#include "irq.h"
#include "fork.h"
#include "sched.h"

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

void process(char *array)
{
	while(1)
	{
		for (int i=0;i<5;i++)
		{
			printf("%c",array[i]);
			delay(100);
		}
	}
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
	
	int res=copy_process((unsigned long)&process, (unsigned long)"12345");
	if(res!=0)
	{
		printf("error while starting process 1");
		return;
	}
	
	res=copy_process((unsigned long)&process, (unsigned long)"abcde");
	if(res!=0)
	{
		printf("error while starting process 2");
		return;
	}


	while(1) 
	{
		schedule();
	}
}
