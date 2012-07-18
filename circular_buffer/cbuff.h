#pragma once
#ifndef _CBUFF_H_
#define _CBUFF_H_

#include <stdlib.h>

/* Circular Buffer: http://en.wikipedia.org/wiki/Circular_buffer
 *     - FIFO
 *     - "The "prized" attribute of a circular buffer is that it
 *       does not need to have its elements shuffled around when one is consumed"
 *     - queue with fixed maximum size
 */

#define CBUFF_EMPTY -1

typedef struct {
    int size; /* fixed size (length) of the circular buffer */
    int last; /* points to the last element */
    int first; /* points to the first/oldest element */
    int* buffer; /* points to buffer storage array */
} cbuff_t;

/* creates and initializes a new cbuff object using the specified fixed size */
cbuff_t* cbuff_init(int size);
void cbuff_dispose(cbuff_t* self);
/* insert an element in the location occurring after the last-modified location.
   if the buffer is full, the oldest element is overwritten. */
void cbuff_add(cbuff_t* self, int element);
/* removes the oldest element and returns its value */
int cbuff_remove(cbuff_t* self);
/* prints the string representation of the circular buffer to stdout. */
void cbuff_inspect(cbuff_t* self);

#endif
