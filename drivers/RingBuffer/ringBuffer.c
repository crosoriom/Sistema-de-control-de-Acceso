#include "ringBuffer.h"

ring_buffer_t ring_buffer_init(uint8_t *mem_add, uint8_t size)
{
    ring_buffer_t rb;

    rb.buffer = mem_add;
    rb.head = 0;
    rb.tail = 0;
    rb.size = size;
    rb.state = EMPTY;

    return rb;
}

void ring_buffer_reset(ring_buffer_t *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->state = EMPTY;
}

uint8_t ring_buffer_getElements(ring_buffer_t *rb)
{
    if(rb->state == FULL)
        return rb->size;

    if(rb->head >= rb->tail)
        return rb->head - rb->tail;
    else
        return rb->size - (rb->tail - rb->head);
}

buffer_state_t ring_buffer_state(ring_buffer_t *rb)
{
    return rb->state;
}

void ring_buffer_write(ring_buffer_t *rb, uint8_t data)
{
    rb->buffer[rb->head] = data;
    rb->head = ++rb->head % rb->size;

    if(rb->head != rb->tail)
        rb->state = WRITTING;
    if(rb->state == WRITTING && rb->head == rb->tail)
        rb->state = FULL;
    if(rb->state == FULL)
        rb->tail = ++rb->tail % rb->size;
}

uint8_t ring_buffer_read(ring_buffer_t *rb, uint8_t *byte)
{
    if(rb->state == EMPTY)
        return 0;

    *byte = rb->buffer[rb->tail];
    rb->tail = ++rb->tail % rb->size;

    if(rb->tail == rb->head)
        rb->state = EMPTY;
    if(rb->state == FULL)
        rb->state = WRITTING;

    return 1;
}
