#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

const int EMPTY = -1;

int inc_index(cbuff_t* self) {
    return (self->last >= self->size) 
        ? 0
        : 1 + self->last;
}

int dec_index(cbuff_t* self) {
    return (0 == self->last) 
        ? self->size - 1
        : self->last - 1;
}

void update_oldest(cbuff_t* self) {
    if (self->oldest == self->last) { 
        /* do nothing */ 
    }
    else if (EMPTY == self->last) {
        self->oldest = EMPTY;
    }
    else if (self->oldest + 1 < self->size) { 
        self->oldest += 1; /* just increment. */
    }
    else { /* loop around */
        self->oldest = 0;
    }
    /* oldest !> last */
    //printf("ERROR: unexpected state: oldest=%d last=%d \n", self->oldest, self->last);
    return;
}

void cbuff_init(cbuff_t* self, int size) {
    int i = 0;
    
    self->last = EMPTY;
    self->oldest = EMPTY;
    self->size = size;
    self->buffer = (int*) malloc(sizeof(int) * size);
    /* clear the buffer contents */
    for (i = 0; i < self->size; i++) {
        self->buffer[i] = EMPTY;
    }
}

void cbuff_dispose(cbuff_t* self) {
    self->last = EMPTY; 
    self->oldest = EMPTY;
    self->size = EMPTY;
    free(self->buffer);
}

void cbuff_add(cbuff_t* self, int element) {
    self->buffer[inc_index(self)] = element;
    self->last += 1; 
}

void cbuff_remove(cbuff_t* self) {
    //critical section
    self->buffer[self->oldest] = EMPTY;
    update_oldest(self);
}

void cbuff_inspect(cbuff_t* self) {
    int i = 0;
    
    printf("circular buffer contents: ");
    
    for (i = 0; i < self->size; i++) {
        if (EMPTY == self->buffer[i]) {
            printf("%d:?", i);
        } 
        else {
            printf("%d:%d", i, self->buffer[i]);
        }
        if (i+1 < self->size) {
            printf(" ");
        }
    }
    
    printf("\n");
}
