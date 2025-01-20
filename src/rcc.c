#include "rcc.h"

#define RCC ((ResetClockControl_t *)0x40021000UL)

void activate_syscfg()
{
	RCC->APB2ENR |= (0x1 << 0);
}

void gpio_activate(uint8_t gpio)
{
	if(gpio == 0xFF)
		return;
	RCC->AHB2ENR |= (0x1 << gpio);
}

void usart2_activate()
{
	RCC->APB1ENR1 |= (0x1 << 17);
}
