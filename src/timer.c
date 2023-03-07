#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void timer_init()
{
	curVal=get32(SYSTEM_TIMER_CLO);
	curVal+=interval;
	put32(SYSTEM_TIMER_C1,curVal);
}

void handle_timer_irq()
{
	curVal+=interval;
	put32(SYSTEM_TIMER_C1,curVal);
	put32(SYSTEM_TIMER_CS,TIMER_CS_M1);
	printf("Timer interrupt received\r\n");
}
