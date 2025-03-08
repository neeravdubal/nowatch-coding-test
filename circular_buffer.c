
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