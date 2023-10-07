#ifndef	_PL011_UART_H
#define	_PL011_UART_H

void pl011_uart_init ( void );
char pl011_uart_recv ( void );
void pl011_uart_send ( char c );
void pl011_uart_send_string(char* str);
void pl011_uart_send_int(int c);
#endif
/*_PL011_UART_H */
