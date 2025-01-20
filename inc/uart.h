#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"

#define USART2 ((usart_t *)0x40004400UL)

#define BAUD_9600_4MHZ (0x1A1)
#define WORD_8BITS_0_9BITS_1 (0x1U << 12)

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t BRR;
    volatile uint32_t GTPR;
    volatile uint32_t RTOR;
    volatile uint32_t RQR;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t RDR;
    volatile uint32_t TDR;
}usart_t;

void configure_gpio_usart(gpio_t *GPIOx, PINx pin);
void usart_init(usart_t *USARTx, gpio_t *GPIOx, PINx tx, PINx rx);

#endif
