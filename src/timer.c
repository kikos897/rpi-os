#include "utils.h"
#include "printf.h"
#include "peripherals/timer.h"

const unsigned int interval = 2000000;
unsigned int curVal = 0;

void timer_init()
{
	printf("\r\ntimer init\r\n");
	curVal=get32(SYSTEM_TIMER_CLO);
	curVal+=interval;
	put32(SYSTEM_TIMER_C1,curVal);
	printf("\r\nsystem_timer_c1=%x",SYSTEM_TIMER_C1);
}

void handle_timer_irq()
{
	curVal+=interval;
	put32(SYSTEM_TIMER_C1,curVal);
	put32(SYSTEM_TIMER_CS,TIMER_CS_M1);
	printf("Timer interrupt received\r\n");
}
