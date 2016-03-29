#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <assert.h>
#include "stack.c"

typedef struct QueueFromStacks {
  Stack *aux;   //auxiliary
  Stack *back;  //data (top is the "back" of the queue)
} QueueFromStacks;

QueueFromStacks *q_init(size_t capacity) {
  QueueFromStacks *q = malloc(sizeof(QueueFromStacks));
  q->aux = stack_init(capacity);
  q->back = stack_init(capacity);
  return q;
}
ptrdiff_t q_size(QueueFromStacks *q) {
  return stack_size(q->back);
}
int q_empty(QueueFromStacks *q) {
  return stack_empty(q->back);
}
int q_full(QueueFromStacks *q) {
  return stack_full(q->back);
}
ItemType q_enqueue(QueueFromStacks *q, ItemType item) {
  if (q_full(q)) {
    return (ItemType) (-1);  // full
  }
  stack_push(q->back, item);
  return item;
}
ItemType q_dequeue(QueueFromStacks *q) {
  if (q_empty(q)) {
    return (ItemType) (-1);  // empty
  }
  if (stack_empty(q->back)) {
    return (ItemType) (-1);  // front is empty
  }
  //up-end the back-stack
  while(!stack_empty(q->back)) {
    stack_push(q->aux, stack_pop(q->back));
  }
  //get the front item
  ItemType front = stack_pop(q->aux);
  //re-form the back-stack
  while(!stack_empty(q->aux)) {
    stack_push(q->back, stack_pop(q->aux));
  }
  return front;
}

void tickle_queue(void) {
  QueueFromStacks *q = q_init(80);
  if (NULL == q) {
    return;
  }
  q_enqueue(q, 1);
  q_enqueue(q, 2);
  q_enqueue(q, 3);
  q_enqueue(q, 4);
  q_enqueue(q, 5);
  q_enqueue(q, 6);
  q_enqueue(q, 7);
  q_enqueue(q, 8);
  for(int i = 0; i < 4; i++) {
    printf("q front: %d\n", q_dequeue(q));
  }
  q_enqueue(q, 32);
  q_enqueue(q, 33);
  q_enqueue(q, 34);
  for(int i = 0; i < 10; i++) {
    printf("q front: %d\n", q_dequeue(q));
  }
  // stack_push(stk, 1024);
  // stack_push(stk, 256);
  // stack_push(stk, 512);
  // printf("max: %d\n", stack_max(stk));
  // while(!stack_empty(stk)) {
  //   printf("%d\n", stack_pop(stk));
  // }
}

int main(int argc, char* argv[]) {
  tickle_queue();
  return 0;
}
