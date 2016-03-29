#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <assert.h>
#include "stack.c"

void hanoi_pretty(Stack *stk1, Stack *stk2, Stack *stk3) {
  printf("\nSTACK 1:\n");
  stack_pretty(stk1);
  printf("\nSTACK 2:\n");
  stack_pretty(stk2);
  printf("\nSTACK 3:\n");
  stack_pretty(stk3);
}

Stack *hanoi_findstart(Stack *stk1, Stack *stk2, Stack *stk3) {
  if ((!stack_empty(stk1) && !stack_empty(stk2))
      || (!stack_empty(stk2) && !stack_empty(stk3))) {
    return NULL; // already started
  }
  if (stack_empty(stk1)) {
    return stk1;
  }
  if (stack_empty(stk2)) {
    return stk2;
  }
  if (stack_empty(stk3)) {
    return stk3;
  }
  assert(0);
}

int hanoi_can_move_to(Stack *from, Stack *to) {
  return (!stack_empty(from)
          && (stack_empty(to)
              || (stack_peek(from) < stack_peek(to))));
}

static Stack *stk1;
static Stack *stk2;
static Stack *stk3;
void hanoi_wait() {
  hanoi_pretty(stk1, stk2, stk3);
  getchar();
}
// Base case: n=1
// Constraints: never undo the previous move
void hanoi_move_n(int n, Stack *this, Stack *to, Stack *aux) {
  if (n > 0) {
    hanoi_move_n(n-1, this, aux, to);
    stack_push(to, stack_pop(this));
    hanoi_wait();
    hanoi_move_n(n-1, aux, to, this);
  }
}

void test_hanoi() {
  stk1 = stack_init(10);
  stk2 = stack_init(10);
  stk3 = stack_init(10);
  stack_push(stk1, 7);
  stack_push(stk1, 6);
  stack_push(stk1, 5);
  stack_push(stk1, 4);
  stack_push(stk1, 3);
  stack_push(stk1, 2);
  stack_push(stk1, 1);
  hanoi_move_n(7, stk1, stk2, stk3);
}

int main(int argc, char* argv[]) {
  test_hanoi();
  // test_stack_tickle();
  return 0;
}
