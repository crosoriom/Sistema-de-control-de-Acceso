#include "uart.h"

void configure_gpio_usart(gpio_t *GPIOx, PINx pin)
{
    configure_gpio_alternateFunctionMode(GPIOx, pin);
    if(pin <= PIN_7) {                                  //select register for mapping de AF7(UART) to pin
        GPIOx->AFRL &= ~(0xFU << (4 * pin));            //resets the register
        GPIOx->AFRL |= (0x7U << (4 * pin));             //writes 0111 in the register
    } else {
        GPIOx->AFRH &= ~(0xFU << (4 * pin));
        GPIOx->AFRH |= (0x7U << (4 * pin));
    }
    GPIOx->OSPEEDR |= (0x3U <<(2 * pin));               //gpio CLK to very high speed for uart com
    GPIOx->PUPDR &= ~(0x3U <<(2 * pin));                //no pull-up pull-down mode
}

void usart_init(usart_t *USARTx, gpio_t *GPIOx, PINx tx, PINx rx)
{
    usart2_activate();
    configure_gpio_usart(GPIOx, tx);
    configure_gpio_usart(GPIOx, rx);

    USARTx->CR1 &= ~(0x1U << 0);                        //disable uart for configuration
    USARTx->BRR = BAUD_9600_4MHZ;                       //set the baud rate
    USARTx->CR1 &= ~WORD_8BITS_0_9BITS_1;               //8 bits world lenght
    USARTx->CR2 &= ~(0x3U << 12);                       //00 set 1 stop bit
    USARTx->CR1 |= (0x1U << 3) | (0x1U << 2);           //enable transmitter and receiver
    USARTx->CR1 |= (0x1U << 0);                         //enable uart
    USARTx->CR1 |= (0x1U << 5);                         //enable rxne interrupt

    NVIC->ISR[1] |= (0x1U << 6);                        //enable usart2 interrupt
}
