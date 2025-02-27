/*
 * ring_buffer.h
 *
 *  Created on: Feb 11, 2025
 *      Author: saaci
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
#include <stdlib.h>

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

} ring_buffer_t;

ring_buffer_t ring_buffer_init(int capacity);
void ring_buffer_reset(ring_buffer_t *rb);
uint8_t ring_buffer_size(ring_buffer_t *rb);
uint8_t ring_buffer_is_full(ring_buffer_t *rb);
uint8_t ring_buffer_is_empty(ring_buffer_t *rb);

void ring_buffer_write(ring_buffer_t *rb, uint8_t data);
uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte);

#endif
