#include "main.h"

#define HEARTBEAT_PIN GPIOA, PIN_5
#define DOOR_STATE GPIOA, PIN_4
#define USER_BUTTON GPIOC, PIN_13

#define TX PIN_2
#define RX PIN_3

#define TIME_UNLOCK 5000

state_t state = LOCKED;

int main(void)
{
    systick_init(4000);
    gpio_interrupt_enable(USER_BUTTON, FALLING_EDGE);
    configure_gpio_output(HEARTBEAT_PIN);
    configure_gpio_output(DOOR_STATE);
    usart_init(USART2, GPIOA, TX, RX, ONE_STOP_BIT, EIGHT_BITS_LENGHT, 115200);

    uint32_t heartbeat_tick = 0;
    while(1)
    {
        if(systick_getTick() - heartbeat_tick >= 500) {
            heartbeat_tick = systick_getTick();
            gpio_toggle_level(HEARTBEAT_PIN);
            usart_send_string(USART2, "Blink");
        }
        switch(state) {
            case LOCKED:
                gpio_set_lowLevel(DOOR_STATE);
                break;
            case TEMPORAL_UNLOCK:
                if(systick_getTick() - heartbeat_tick >= TIME_UNLOCK)
                    state = 0;
                break;
            case PERMANENT_UNLOCK:
                break;
        }
                
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1 << 13)) {
        gpio_set_highLevel(DOOR_STATE);
        if(state == LOCKED)
            state = TEMPORAL_UNLOCK;
        else if(state == TEMPORAL_UNLOCK)
            state = PERMANENT_UNLOCK;
        else
            state = LOCKED;
    }
}
