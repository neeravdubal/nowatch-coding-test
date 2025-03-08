
#include <stdio.h>

#include "circular_buffer.h"

CircularBuffer* cb_init(size_t capacity) 
{
    CircularBuffer *cb = malloc(sizeof(CircularBuffer));
    if (!cb) return NULL;
    
    cb->buffer = malloc(sizeof(int) * capacity);

    if (!cb->buffer) 
    {
        free(cb);
        return NULL;
    }
    
    cb->capacity = capacity;
    cb->head = 0;
    cb->tail = 0;
    cb->full = false;
    return cb;
}

void cb_free(CircularBuffer *cb) 
{
    if (cb) 
    {
        free(cb->buffer);
        free(cb);
    }
}

bool cb_is_empty(CircularBuffer *cb) 
{
    /* If not full, buffer is empty when head equals tail. */
    return (!cb->full && (cb->head == cb->tail));
}

bool cb_is_full(CircularBuffer *cb) 
{
    return cb->full;
}

void cb_add(CircularBuffer *cb, int data) 
{
    /* When the buffer is full, advance tail to overwrite the oldest element. */
    if (cb->full) 
    {
        cb->tail = (cb->tail + 1) % cb->capacity;
    }
    
    cb->buffer[cb->head] = data;

    cb->head = (cb->head + 1) % cb->capacity;
    
    /* Mark the buffer as full if head has caught up with tail. */
    cb->full = (cb->head == cb->tail);
}

int32_t cb_remove(CircularBuffer *cb, int *data) 
{
    if (cb_is_empty(cb)) 
    {
        return -1;  /* Nothing to remove */
    }
    
    *data = cb->buffer[cb->tail];

    cb->full = false;

    cb->tail = (cb->tail + 1) % cb->capacity;

    return 0;
}

size_t cb_size(CircularBuffer *cb) 
{
    size_t size = cb->capacity;
    
    if (!cb->full) 
    {
        if (cb->head >= cb->tail) 
        {
            size = cb->head - cb->tail;
        } 
        else 
        {
            size = cb->capacity + cb->head - cb->tail;
        }
    }

    return size;
}
