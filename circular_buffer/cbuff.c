#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

void cbuff_init(cbuff_t* self, int size) {
    self->size = size;
    self->buffer = (int*) malloc (sizeof(int) * size);
}

void cbuff_dispose(cbuff_t* self) {
    free(self->buffer);
}

void cbuff_add(cbuff_t* self, int element) {
    printf("circular buffer size: %d\n", self->size);
}

void cbuff_remove(cbuff_t* self) {
}

