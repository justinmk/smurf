#include <stdlib.h>

typedef struct {
    int size; /* fixed size (length) of the circular buffer */
    int last; /* points to the last element */
    int* buffer; /* points to buffer storage array */
} cbuff_t;

/* allocate space; set start location */
void cbuff_init(cbuff_t* self, int size);
void cbuff_dispose(cbuff_t* self);
/* insert an element in the location occurring after the last-modified location. 
   if the buffer is full, the oldest element is overwritten. */
void cbuff_add(cbuff_t* self, int element);
/* removes the oldest element */
void cbuff_remove(cbuff_t* self);
/* prints the string representation of the circular buffer to stdout. */
void cbuff_inspect(cbuff_t* self);
