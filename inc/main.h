#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include "systick.h"
#include "KeyPad/keypad.h"
#include "gpio.h"
#include "exti.h"
#include "uart.h"
/*
typedef enum {
    LOCKED = 0,
    TEMPORAL_UNLOCK,
    PERMANENT_UNLOCK
}state_t;
*/

#define KEYPAD_ROWS_PINS {PIN_2, PIN_3, PIN_8, PIN_9}
#define KEYPAD_COLS_PINS {PIN_5, PIN_10, PIN_11, PIN_12}

keypad_t keypad = {
    .GPIOx = GPIOC,
    .rowPins = KEYPAD_ROWS_PINS,
    .colPins = KEYPAD_COLS_PINS
};
char key;

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1 << 13))
        EXTI->PR1 = (1 << 13);
    if(EXTI->PR1 & (1 << 12)) {
        key = keypad_scan(keypad, 3);
        EXTI->PR1 = (1 << 12);
    }
    if(EXTI->PR1 & (1 << 11)) {
        key = keypad_scan(keypad, 2);
        EXTI->PR1 = (1 << 11);
    }
    if(EXTI->PR1 & (1 << 10)) {
        key = keypad_scan(keypad, 1);
        EXTI->PR1 = (1 << 10);
    }
}

void EXTI9_5_IRQHandler()
{
    if (EXTI->PR1 & (1 << 9))
        EXTI->PR1 = (1 << 9);
    if (EXTI->PR1 & (1 << 8))
        EXTI->PR1 = (1 << 8);
    if (EXTI->PR1 & (1 << 7))
        EXTI->PR1 = (1 << 7);
    if (EXTI->PR1 & (1 << 6))
        EXTI->PR1 = (1 << 6);
    if (EXTI->PR1 & (1 << 5)) {
        key = keypad_scan(keypad, 0);
        EXTI->PR1 = (1 << 5);
    }
}

#endif
