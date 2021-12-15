#include "delay.h"


void delay_ms(uint16_t nms)
{
	usleep(nms*1000);
	
}
void delay_us(uint32_t nus)
{
	
	usleep(nus);
}
