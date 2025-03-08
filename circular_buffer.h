ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

/* Define the CircularBuffer structure to store integers. */
typedef struct {
    int32_t *buffer;      /* Pointer to the allocated array */
    size_t head;      /* Index where the next element will be inserted */
    size_t tail;      /* Index of the oldest element for removal */
    size_t capacity;  /* Maximum number of elements in the buffer */
    bool full;        /* Flag to indicate if the buffer is full */
} CircularBuffer;

/* Initializes a circular buffer with specified capacity.
 * Returns a pointer to the new CircularBuffer struct or NULL if allocation fails. */
CircularBuffer* cb_init(size_t capacity);

/* Frees the memory allocated for the circular buffer. */
void cb_free(CircularBuffer *cb);

/* Returns true if the circular buffer is empty. */
bool cb_is_empty(CircularBuffer *cb);

/* Returns true if the circular buffer is full. */
bool cb_is_full(CircularBuffer *cb);

/* Adds an element to the circular buffer.
 * If the buffer is full, it automatically overwrites the oldest element. */
void cb_add(CircularBuffer *cb, int data);

/* Removes the oldest element from the buffer.
 * The removed element is stored into the integer pointed by 'data'.
 * Returns 0 on success; returns -1 if the buffer is empty. */
int32_t cb_remove(CircularBuffer *cb, int *data);

/* Returns the current number of elements stored in the circular buffer. */
size_t cb_size(CircularBuffer *cb);

/* Computes the Exponential Moving Average (EMA) over all values in the circular buffer.
 * 'alpha' is the smoothing factor (0 < alpha <= 1). Returns 0.0 if the buffer is empty. */
double compute_ema(CircularBuffer *cb, double alpha);

#endif /* CIRCULAR_BUFFER_H */