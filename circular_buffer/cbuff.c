#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

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

void cbuff_init(cbuff_t* self, int size) {
    int i = 0;
    
    self->last = -1;
    self->size = size;
    self->buffer = (int*) malloc(sizeof(int) * size);
    /* clear the buffer contents */
    for (i = 0; i < self->size; i++) {
        self->buffer[i] = NULL;
    }
}

void cbuff_dispose(cbuff_t* self) {
    self->last = 0; 
    self->size = 0;
    free(self->buffer);
}

void cbuff_add(cbuff_t* self, int element) {
    self->buffer[inc_index(self)] = element;
    self->last += 1; 
}

void cbuff_remove(cbuff_t* self) {
    self->buffer[self->last] = 0;
    self->last = dec_index(self); 
}

void cbuff_inspect(cbuff_t* self) {
    int i = 0;
    
    printf("circular buffer contents: ");
    
    for (i = 0; i < self->size; i++) {
        if (NULL == self->buffer[i]) {
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
