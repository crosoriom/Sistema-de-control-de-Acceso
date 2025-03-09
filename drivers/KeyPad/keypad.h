#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>
#include "gpio.h"
#include "exti.h"

typedef struct {
    gpio_t *GPIOx;
    PINx rowPins[4];
    PINx colPins[4];
}keypad_t;

void keypad_init(keypad_t keyboard);
uint8_t keypad_scan(keypad_t keyboard, uint8_t colPin);
#endif
