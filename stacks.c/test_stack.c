#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <assert.h>
#include "stack.c"

void test_stack_tickle(void) {
  Stack *stk = stack_init(80);
  if (NULL == stk) {
    return;
  }
  stack_push(stk, 1);
  stack_push(stk, 2);
  stack_push(stk, 3);
  stack_push(stk, 4);
  stack_push(stk, 5);
  stack_push(stk, 10);
  stack_push(stk, 6);
  stack_push(stk, 7);
  stack_pretty(stk);
  printf("max: %d\n", stack_max(stk));
  stack_push(stk, 8);
  stack_push(stk, 9);
  printf("max: %d\n", stack_max(stk));
  while(!stack_empty(stk)) {
    printf("%d\n", stack_pop(stk));
  }
  stack_push(stk, 1024);
  stack_push(stk, 256);
  stack_push(stk, 512);
  printf("max: %d\n", stack_max(stk));
  while(!stack_empty(stk)) {
    printf("%d\n", stack_pop(stk));
  }
}

int main(int argc, char* argv[]) {
  test_stack_tickle();
  return 0;
}
