/*
 * ring_buffer.h
 *
 *  Created on: Feb 11, 2025
 *      Author: saaci
 *  Modified by:
 *  	Cristian Camilo Osorio
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdint.h>

typedef enum {
    EMPTY,
    WRITTING,
    FULL
} buffer_state_t;

typedef struct {
	volatile uint8_t *buffer;
	volatile uint8_t head;
	volatile uint8_t tail;
	volatile uint8_t size;
	volatile buffer_state_t state;
} ring_buffer_t;

/**
 * @brief Crea e inicializa una estructura RingBuffer
 *
 * La función crea una estructura RingBuffer e inicializa
 * sus propiedades.
 *
 * @param[in] *memory Dirección donde se almacenará la
 * estructura
 * @param[in] capacity Tamaño a reservar para la capacidad
 * del buffer
 *
 * @return Estructura tipo RingBuffer
 */
ring_buffer_t ring_buffer_init(uint8_t *memory, uint8_t capacity);

/**
 * @brief Reinicia la cabeza y la cola del Buffer
 *
 * La función se encarga de hacer que el RingBuffer se
 * escriba desde cero, es decir, ignora los datos que
 * tenía escritos y reescribe sobre ellos, actuando como
 * si estuviera vacío.
 *
 * @param[in] *rb Puntero al RingBuffer
 *
 * @warning Si se resetea un Buffer, no habrá forma de
 * acceder a los datos que tenía escritos antes del reset.
 */
void ring_buffer_reset(ring_buffer_t *rb);

/**
 * @brief Retorna el número de elementos en el Buffer
 *
 * La función se encarga de hacer los calculos, basados
 * en la posición de la cabeza y la cola, para establecer
 * cuantos elementos hay almacenados en el RingBuffer.
 * 
 * @param[in] *rb Puntero al RingBuffer
 *
 * @return Cantidad de elementos en el Buffer
 */
uint8_t ring_buffer_getElements(ring_buffer_t *rb);

/**
 * @brief Verifica el estado del Buffer
 *
 *La función retorna el estado actual del RingBuffer.

 @param[in] *rb Puntero al RingBuffer

 @return Enumeración del estado del Buffer
 */
buffer_state_t ring_buffer_state(ring_buffer_t *rb);

void ring_buffer_write(ring_buffer_t *rb, uint8_t data);

uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte);

#endif
