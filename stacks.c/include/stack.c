#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <assert.h>

typedef int ItemType;
typedef struct Stack {
  ItemType *bot;  // never changes
  ItemType *top;  // current position
  size_t    capacity;
} Stack;

Stack *stack_init(size_t capacity) {
  if (capacity <= 0) {
    return NULL;
  }
  Stack *stk = malloc(sizeof(Stack));
  stk->bot = malloc((capacity * sizeof(*stk->bot)));
  stk->top = NULL;
  stk->capacity = capacity;
  return stk;
}

int stack_free(Stack *stk) {
  if (NULL == stk) {
    return 0;
  }
  free(stk->bot);
  free(stk);
  return 1;
}
int stack_empty(Stack *stk) {
  return stk->top == NULL;
}
ptrdiff_t stack_size(Stack *stk) {
  return stack_empty(stk) ? (ptrdiff_t)0 : (stk->top - stk->bot);
}
int stack_full(Stack *stk) {
  return stack_size(stk) == stk->capacity;
}
int stack_peek(Stack *stk) {
  if (stack_empty(stk)) {
    return -1;
  }
  return *(stk->top);
}
ItemType stack_pop(Stack *stk) {
  assert(stack_size(stk) <= stk->capacity);
  if (stack_empty(stk)) {
    return (ItemType) (-1);  // empty
  }
  ItemType item = *(stk->top);
  stk->top = (stk->top == stk->bot) ? NULL : (stk->top - 1);
  return item;
}
ItemType stack_push(Stack *stk, ItemType item) {
  assert(stack_size(stk) <= stk->capacity);
  if (stack_full(stk)) {
    return (ItemType) (-1);  // full
  }
  stk->top = stack_empty(stk) ? stk->bot : (stk->top + 1);
  *(stk->top) = item;
  return item;
}
int stack_max(Stack *stk) {
  int max = 0;
  if (stack_empty(stk)) {
    return 0;
  }
  for(ItemType *p = stk->bot; ; p++) {
    if ((int) *p > max) {
      max = (int) *p;
    }
    if (p == stk->top) {
      break;
    }
  }
  return max;
}
void stack_pretty(Stack *stk) {
  if (stack_empty(stk)) {
    printf("[empty]\n");
  }
  for(int i = 1; i <= stack_max(stk); i++) {
    for (ItemType *p = stk->bot; ; p++) {
      if ((int) *p >= i) {
        printf("#");
      } else {
        printf(" ");
      }
      if (p == stk->top) {
        break;
      }
    }
    printf("\n");
  }
}

