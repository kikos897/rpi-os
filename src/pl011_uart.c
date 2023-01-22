#include "utils.h"
#include "peripherals/pl011_uart.h"
#include "peripherals/gpio.h"


void pl011_uart_init ( void )
{
	unsigned int selector;
	
	selector = get32(GPFSEL0);
	selector &= ~(7<<24);                   // clean gpio8
	selector |= 3<<24;                      // set alt0 for gpio8
	selector &= ~(7<<27);                   // clean gpio9
	selector |= 3<<27;                      // set alt0 for gpio9
	put32(GPFSEL0,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<8)|(1<<9));
	delay(150);
	put32(GPPUDCLK0,0);
	
	put32(UART_IBRD, 26);
	put32(UART_FBRD, 3);
	put32(UART_LCRH, (3u << 5));                // set WLEN to 0b11
	put32(UART_CR, (1u << 9) | (1u << 8) | 1u); 

}

void pl011_uart_send ( char c )
{
	while(get32(UART_FR)&0x20);
	put32(UART_DR,c);
}

void pl011_uart_send_int ( int c )
{
	while(get32(UART_FR)&0x20);
	put32(UART_DR,c+0x30);
}

char pl011_uart_recv ( void )
{
	while(get32(UART_FR)&0x10);
	return(get32(UART_DR)&0xFF);
}

void pl011_uart_send_string(char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		pl011_uart_send((char)str[i]);
	}
}
