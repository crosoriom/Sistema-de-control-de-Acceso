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

void usart_activate(uint8_t usart)
{
	switch(usart) {
		case 1:
			RCC->APB2ENR |= (0x1 << 14);
		case 2:
			RCC->APB1ENR1 |= (0x1 << 17);
		case 3:
			RCC->APB1ENR1 |= (0x1 << 18);
		case 4:
			RCC->APB1ENR1 |= (0x1 << 19);
		case 5:
			RCC->APB1ENR1 |= (0x1 << 20);
	}
}
