#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "gpio.h"
#include "exti.h"
#include "rcc.h"

#define USART1 ((usart_t *)0x40013800UL)
#define USART2 ((usart_t *)0x40004400UL)
#define USART3 ((usart_t *)0x40004800UL)
#define UART_4 ((usart_t *)0x40004C00UL)
#define UART_5 ((usart_t *)0x40005000UL)

#define USART_ENABLE (0x1U <<0)
#define TX_ENABLE (0x1U << 3)
#define RX_ENABLE (0x1U << 2)
#define TRANSMIT_ENABLE (0x1U << 7)

#define BAUD_9600_4MHZ (0x1A1)
#define WORD_8BITS_0_9BITS_1 (0x1U << 12)
#define WORD_7BITS (0x1U << 28) | ~(0x1U << 12)

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

typedef enum {
    HALF_STOP_BIT,
    ONE_STOP_BIT,
    ONE_HALF_STOP_BIT,
    TWO_STOP_BITS
}stopBit_t;

typedef enum {
    SEVEN_BITS_LENGHT,
    EIGHT_BITS_LENGHT,
    NINE_BITS_LENGHT
}lenghtBit_t;

/**
 * @brief La función configura pines GPIO para comunicación USART.
 *
 * La función configura dos pines GPIO usarlo como puerto para la 
 * comunicación serial. Además se encarga de manipular los 
 * registros del periférico de comunicación con los argumentos 
 * deseados.
 *
 * @param *USARTx dirección del periferico que se va a configurar.
 *                  - USART1, USART2, USART3
 * @param *GPIOx dirección al puerto GPIO de los pines a usar como
 * terminal
 * @param tx Enumeración del pin transmisor.
 * @param rx Enumeración del pin receptor.
 * @param stop Enumeración para los bits de parada.
 * @param wordLengt Enumeración para la longitud de los mensajes.
 * @param baudRate Cantidad de Bauds por segundo.
 *
 * @note Usar unicamente para comunicación USART, puesto que la
 * función necesita pin receptor y transmisor.
 */
void usart_init(usart_t *USARTx, gpio_t *GPIOx, PINx tx, PINx rx, stopBit_t stop, lenghtBit_t wordLengt, int baudrate);
void usart_set_stop_bits(usart_t *USARTx, stopBit_t stop);
void usart_set_word_lenght(usart_t *USARTx, lenghtBit_t lenght);
void enable_RXNE(usart_t *USARTx);
void usart_send_string(usart_t *USARTx, const char *str);

#endif
