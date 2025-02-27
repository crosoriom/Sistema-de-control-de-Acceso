#include "uart.h"

int usart_number(usart_t *USARTx)
{
    if(USARTx == USART1)
        return 1;
    else if(USARTx == USART2)
        return 2;
    else if(USARTx == USART3)
        return 3;
    else if(USARTx == UART_4)
        return 4;
    else
        return 5;
}

void usart_init(usart_t *USARTx, gpio_t *GPIOx, PINx tx, PINx rx, stopBit_t stop, lenghtBit_t wordLenght, int baudRate)
{
    usart_activate(usart_number(USARTx));

    configure_gpio_usart(GPIOx, tx);
    configure_gpio_usart(GPIOx, rx);

    USARTx->CR1 &= ~USART_ENABLE;                       //disable uart for configuration
    USARTx->BRR = 4000000 / baudRate;                   //set the baud rate
    usart_set_word_lenght(USARTx, wordLenght);
    usart_set_stop_bits(USARTx, stop);
    USARTx->CR1 |= TX_ENABLE | RX_ENABLE;               //enable tx and rx
    USARTx->CR1 |= USART_ENABLE;                        //enable uart
}

void usart_set_stop_bits(usart_t *USARTx, stopBit_t stop)
{
    switch(stop) {
        case HALF_STOP_BIT:
            USARTx->CR2 &= ~(0x3U << 12);
            USARTx->CR2 |= (0x1U << 12);
            break;
        case ONE_STOP_BIT:
            USARTx->CR2 &= ~(0x3U << 12);
            break;
        case ONE_HALF_STOP_BIT:
            USARTx->CR2 |= (0x3U << 12);
            break;
        case TWO_STOP_BITS:
            USARTx->CR2 &= ~(0x3U << 12);
            USARTx->CR2 |= (0x2U << 12);
            break;
    }
}

void usart_set_word_lenght(usart_t *USARTx, lenghtBit_t lenght)
{
    switch(lenght) {
        case EIGHT_BITS_LENGHT:
            USARTx->CR1 &= ~WORD_8BITS_0_9BITS_1;
            break;
        case NINE_BITS_LENGHT:
            USARTx->CR1 |= WORD_8BITS_0_9BITS_1;
            break;
        case SEVEN_BITS_LENGHT:
            USARTx->CR1 |= WORD_7BITS;
            break;
    }
}

void enable_RXNE(usart_t *USARTx)
{
    USARTx->CR1 |= (0x1U << 5);                         //enable RXNEIE register for lauching the RXNE interrupt
    usart_interrupt_enable(usart_number(USARTx));
}

void usart_send_string(usart_t *USARTx, const char *str)
{
    while(*str) {
        while(!(USARTx->ISR & TRANSMIT_ENABLE));
        USARTx->TDR = (*str++); //& 0xFF;
    }
}

