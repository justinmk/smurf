#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

void inc_first(cbuff_t* self) {
    if (self->first != self->last) {
        self->first = (self->first + 1) % self->size;
    }
    else {
        /* else, we just removed the last element, which was also the first,
           so there are no elements left. */
        self->last = CBUFF_EMPTY;
        self->first = CBUFF_EMPTY;
    }
}

//update 'last' BEFORE APPENDING an element.
void inc_last(cbuff_t* self) {
    int i = 0;

    i = (self->last + 1) % self->size;

    /* if we wrapped around to the first element, it is now "last" and
       the next element becomes "first". */
    if (i == self->first) {
        inc_first(self);
    }

    self->last = i;
}

cbuff_t* cbuff_init(int size) {
    int i = 0;
    cbuff_t* self;

    self = (cbuff_t*) malloc(sizeof(cbuff_t));
    self->first = CBUFF_EMPTY;
    self->last = CBUFF_EMPTY;
    self->size = size;
    self->buffer = (int*) malloc(sizeof(int) * size);
    /* clear the buffer contents */
    for (i = 0; i < self->size; i++) {
        self->buffer[i] = CBUFF_EMPTY;
    }

    return self;
}

void cbuff_dispose(cbuff_t* self) {
    self->first = CBUFF_EMPTY;
    self->last = CBUFF_EMPTY;
    self->size = 0;
    free(self->buffer);
}

void cbuff_add(cbuff_t* self, int element) {
    //critical section
    inc_last(self);
    self->buffer[self->last] = element;
    //special case: an CBUFF_EMPTY cbuff
    if (CBUFF_EMPTY == self->first) {
        inc_first(self);
    }
}

int cbuff_remove(cbuff_t* self) {
    int val = CBUFF_EMPTY;

    //special case
    if (CBUFF_EMPTY == self->first) {
        return CBUFF_EMPTY; //do nothing
    }

    //critical section
    val = self->buffer[self->first];
    self->buffer[self->first] = CBUFF_EMPTY;
    inc_first(self);

    return val;
}

void cbuff_inspect(cbuff_t* self) {
    int i = 0;

    printf("circular buffer contents: ");

    for (i = 0; i < self->size; i++) {
        if (CBUFF_EMPTY == self->buffer[i]) {
            if (i == self->first) {
                if (i == self->last) {
                    printf("[:]");
                }
                else {
                    printf("[_]");
                }
            }
            else if (i == self->last) {
                if (i == self->first) {
                    printf("[:]");
                }
                else {
                    printf(":_:");
                }
            }
            else {
                printf(" _ ");
            }
        }
        else {
            if (i == self->first && i == self->last) {
                printf("[%d:", self->buffer[i]);
            }
            else if (i == self->first) {
                printf("[%d]", self->buffer[i]);
            }
            else if (i == self->last) {
                printf(":%d:", self->buffer[i]);
            }
            else {
                printf(" %d ", self->buffer[i]);
            }
        }
        if (i+1 < self->size) {
            printf(" ");
        }
    }

    printf("\n");
}

