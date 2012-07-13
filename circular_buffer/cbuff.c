#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

const int EMPTY = -1;

//update 'oldest' after removing the oldest element. 
void update_oldest(cbuff_t* self) {
    if (self->oldest == self->last) { 
        /* do nothing */ 
    }
    else if (self->oldest + 1 < self->size) { 
        self->oldest += 1; /* just increment. */
    }
    else { /* loop around */
        self->oldest = 0;
    }
    /* oldest !> last */
    //printf("ERROR: unexpected state: oldest=%d last=%d \n", self->oldest, self->last);
}

//update 'last' after appending an element. 
void update_last(cbuff_t* self) {
    int i = 0;

    i = (self->last + 1 == self->size) ? 0 : 1 + self->last;

    /* if we wrapped around to the oldest element, it is no longer 
     * the oldest, because we are overwriting it. */
    if (i == self->oldest) { 
        update_oldest(self);
    }

    self->last = i;
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
    self->last = 0; 
    self->oldest = 0;
    self->size = 0;
    free(self->buffer);
}

void cbuff_add(cbuff_t* self, int element) {
    //critical section
    update_last(self);
    self->buffer[self->last] = element;
    //special case
    if (EMPTY == self->oldest) {
        update_oldest(self);
    }
}

void cbuff_remove(cbuff_t* self) {
    //special case
    if (EMPTY == self->oldest) {
        return; //do nothing
    }
    //critical section
    self->buffer[self->oldest] = EMPTY;
    update_oldest(self);
}

void cbuff_inspect(cbuff_t* self) {
    int i = 0;
    
    printf("circular buffer contents: ");
    
    for (i = 0; i < self->size; i++) {
        if (EMPTY == self->buffer[i]) {
            if (i == self->last) {
                if (i == self->oldest) {
                    printf("[^]");
                }
                else {
                    printf(" ^ ");
                }
            }
            else {
                printf(" _ ");
            }
        } 
        else {
            if (i == self->oldest) {
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

