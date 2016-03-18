#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

typedef int ItemType;
typedef struct Stack {
  ItemType *bot;
  ItemType *top;
  size_t    capacity;
} Stack;

Stack *stack_init(size_t capacity) {
  Stack *stk = malloc(sizeof(Stack) + (capacity * sizeof(ItemType)));
  stk->bot = malloc((capacity * sizeof(ItemType)));
  stk->top = stk->bot;
  stk->capacity = capacity;
}

int stack_free(Stack *stk) {
  if (NULL == stk) {
    return 0;
  }
  free(stk);
  return 1;
}
int stack_empty(Stack *stk) {
  return stk->bot == stk->top;
}
int stack_full(Stack *stk) {
  assert(stk->top - stk->bot <= stk->capacity);
  return (stk->top - stk->bot) == (stk->capacity - 1);
}
int stack_peek(Stack *stk) {
}
ItemType stack_pop(Stack *stk) {
  assert(stk->top - stk->bot <= stk->capacity);
  ItemType item;
  if (stack_empty(stk)) {
    return (ItemType)-1;  // empty
  }
  item = *(stk->bot + stk->top);
  stk->top--;
  return item;
}
int stack_push(Stack *stk, ItemType item) {
  assert(stk->top - stk->bot <= stk->capacity);
  if (stack_full(stk)) {
    return -1;            // full
  }
  stk->top++;
  *(stk->bot + stk->top) = item;
}
int stack_count(Stack *stk) {
}

void test_stack_tickle(void) {
  Stack *stk = stack_init(80);
  if (NULL == stk) {
    return;
  }
  printf("cap: %d top: %d\n", stk->capacity, stk->top);
  stack_push(stk, 1);
  // stack_push(stk, 2);
  // stack_push(stk, 3);
  // stack_push(stk, 4);
  // stack_push(stk, 5);
  // stack_push(stk, 6);
  // stack_push(stk, 7);
  // stack_push(stk, 8);
  // stack_push(stk, 9);
  // stack_push(stk, 10);
  while(!stack_empty(stk)) {
    printf("%d\n", stack_pop(stk));
  }
  // stack_push(stk, 256);
  // stack_push(stk, 512);
  // stack_push(stk, 1024);
  // while(!stack_empty(stk)) {
  //   printf("%d\n", stack_pop(stk));
  // }
  // printf("%d\n", stack_pop(stk));
}

int main(int argc, char* argv[]) {
  test_stack_tickle();
  return 0;
}
