#include "main.h"

#define HEARTBEAT_PIN GPIOA, PIN_5
#define DOOR_STATE GPIOA, PIN_4
#define USER_BUTTON GPIOC, PIN_13

#define TX PIN_2
#define RX PIN_3

#define TIME_UNLOCK 5000

state_t state = LOCKED;
//extern char key;
//extern keypad_t keypad;

uint32_t heartbeat_tick = 0;
uint32_t unlock_tick;

int main(void)
{
    systick_init(4000);
    gpio_interrupt_enable(USER_BUTTON, FALLING_EDGE);
    configure_gpio_output(HEARTBEAT_PIN);
    configure_gpio_output(DOOR_STATE);
    usart_init(USART2, GPIOA, TX, RX, ONE_STOP_BIT, EIGHT_BITS_LENGHT, 115200);
    //keypad_init(keypad);
    usart_send_string(USART2, "MC started!\n");

    int heartbeatDelay;
    while(1)
    {
        switch(state) {
            case LOCKED:
                heartbeatDelay = 500;
                break;
            case TEMPORAL_UNLOCK:
                heartbeatDelay = 250;
                if(systick_getTick() - unlock_tick >= TIME_UNLOCK)
                    state = 0;
                break;
            case PERMANENT_UNLOCK:
                heartbeatDelay = 100;
                break;
        }

        if(systick_getTick() - heartbeat_tick >= heartbeatDelay) {
            heartbeat_tick = systick_getTick();
            gpio_toggle_level(HEARTBEAT_PIN);
        }
        //if(key != 0) {
        //    usart_send_string(USART2, &key);
        //    key = 0;
        //}
    }
}

void eventHandler(event_t event)
{
    char* word;
    switch(event) {
        case BUTTON:
            usart_send_string(USART2, "Button pressed, changing door state.");
            if(state == LOCKED) {
                unlock_tick = systick_getTick();
                state = TEMPORAL_UNLOCK;
                gpio_set_highLevel(DOOR_STATE);
            }
            else if(state == TEMPORAL_UNLOCK)
                state = PERMANENT_UNLOCK;
            else {
                state = LOCKED;
                gpio_set_lowLevel(DOOR_STATE);
            }
        case USART:
            word = usart_receive_string(USART2);
            usart_send_string(USART2, word);
    }
}
