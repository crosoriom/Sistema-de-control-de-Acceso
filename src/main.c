#include "main.h"

#define HEARTBEAT_PIN GPIOA, PIN_5
#define DOOR_STATE GPIOA, PIN_4
#define USER_BUTTON GPIOC, PIN_13

#define TX PIN_2
#define RX PIN_3

#define TIME_UNLOCK 5000

//state_t state = LOCKED;
//volatile char mesage[] = "Blink\n";
extern char key;
extern keypad_t keypad;

int main(void)
{
    systick_init(4000);
    gpio_interrupt_enable(USER_BUTTON, FALLING_EDGE);
    configure_gpio_output(HEARTBEAT_PIN);
    //configure_gpio_output(DOOR_STATE);
    usart_init(USART2, GPIOA, TX, RX, ONE_STOP_BIT, EIGHT_BITS_LENGHT, 115200);
    keypad_init(keypad);
    usart_send_string(USART2, "MC started!\n");

    uint32_t heartbeat_tick = 0;
    while(1)
    {
        if(systick_getTick() - heartbeat_tick >= 500) {
            heartbeat_tick = systick_getTick();
            gpio_toggle_level(HEARTBEAT_PIN);
        }
        if(key != 0) {
            usart_send_string(USART2, &key);
            key = 0;
        }
        //switch(state) {
        //    case LOCKED:
        //        gpio_set_lowLevel(DOOR_STATE);
        //        break;
        //    case TEMPORAL_UNLOCK:
        //        if(systick_getTick() - heartbeat_tick >= TIME_UNLOCK)
        //            state = 0;
        //        break;
        //    case PERMANENT_UNLOCK:
        //        break;
        //}
                
    }
}

