#include <stdio.h>
#include <stdlib.h>
#include "cbuff.h"

const int EMPTY = -1;

void update_first_after_remove(cbuff_t* self) {
    if (self->first == self->last) { 
        //we just removed the last element, which was also the first,
        //so there are no elements left.
        self->last = EMPTY;
        self->first = EMPTY;
    }
    else if (self->first + 1 < self->size) { 
        self->first += 1; /* just increment. */
    }
    else { /* loop around */
        self->first = 0;
    }
    /* first !> last */
    //printf("ERROR: unexpected state: first=%d last=%d \n", self->first, self->last);
}

//update 'last' BEFORE APPENDING an element. 
void update_last_before_add(cbuff_t* self) {
    int i = 0;

    i = (self->last + 1) % self->size;

    /* if we wrapped around to the first element, it is now "last" and 
       the next element becomes "first". */
    if (i == self->first) { 
        update_first_after_remove(self);
    }

    self->last = i;
}

void cbuff_init(cbuff_t* self, int size) {
    int i = 0;
    
    self->last = EMPTY;
    self->first = EMPTY;
    self->size = size;
    self->buffer = (int*) malloc(sizeof(int) * size);
    /* clear the buffer contents */
    for (i = 0; i < self->size; i++) {
        self->buffer[i] = EMPTY;
    }
}

void cbuff_dispose(cbuff_t* self) {
    self->last = 0; 
    self->first = 0;
    self->size = 0;
    free(self->buffer);
}

void cbuff_add(cbuff_t* self, int element) {
    //critical section
    update_last_before_add(self);
    self->buffer[self->last] = element;
    //special case
    if (EMPTY == self->first) {
        update_first_after_remove(self);
    }
}

void cbuff_remove(cbuff_t* self) {
    //special case
    if (EMPTY == self->first) {
        return; //do nothing
    }
    //critical section
    self->buffer[self->first] = EMPTY;
    update_first_after_remove(self);
}

void cbuff_inspect(cbuff_t* self) {
    int i = 0;
    
    printf("circular buffer contents: ");
    
    for (i = 0; i < self->size; i++) {
        if (EMPTY == self->buffer[i]) {
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
            if (i == self->first) {
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

