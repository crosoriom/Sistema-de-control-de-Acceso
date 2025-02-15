#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>
#include "syscfg.h"
#include "uart.h"
#include "gpio.h"
#include "nvic.h"

#define EXTI ((ExtendedInterrupts_t *)0x40010400UL)

typedef struct {
    volatile uint32_t IMR1;
    volatile uint32_t EMR1;
    volatile uint32_t RTSR1;
    volatile uint32_t FTSR1;
    volatile uint32_t SWIER1;
    volatile uint32_t PR1;
    volatile uint32_t RESERVED[3];
    volatile uint32_t IMR2;
    volatile uint32_t EMR2;
    volatile uint32_t RTSR2;
    volatile uint32_t FTSR2;
    volatile uint32_t SWIER2;
    volatile uint32_t PR2;
}ExtendedInterrupts_t;

typedef enum {
    RISING_EDGE,
    FALLING_EDGE,
    BOTH_EDGES
}Trigger_t;

void gpio_interrupt_enable(gpio_t *GPIOx, PINx pin, Trigger_t trigger);
void usart_interrupt_enable(usart_t *USARTx);

#endif
