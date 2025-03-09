#include "keypad.h"

#define DELAY 1000

const char keymap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void keypad_init(keypad_t keyboard)
{
    for(int i = 0; i < 4; i++) {
        configure_gpio_ODmode(keyboard.GPIOx, keyboard.rowPins[i]);
        gpio_set_lowLevel(keyboard.GPIOx, keyboard.rowPins[i]);
        gpio_interrupt_enable(keyboard.GPIOx, keyboard.colPins[i], FALLING_EDGE);
    }
}

uint8_t keypad_scan(keypad_t keyboard,uint8_t columnPin)
{
    int i;
    for(i = 0; i < 4; i++) {
        gpio_set_highLevel(keyboard.GPIOx, keyboard.rowPins[i]);
        for(int j = 0; j <= DELAY; j++)
            ;
        if(gpio_getLevel(keyboard.GPIOx, keyboard.colPins[columnPin], PULLUP) == 1) {
            keypad_init(keyboard);
            return keymap[i][columnPin];
        }
        keypad_init(keyboard);
    }

    return 0;
}
