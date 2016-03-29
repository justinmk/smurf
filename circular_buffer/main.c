#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define ERR_EMPTY INT32_MAX;

typedef int ItemType;
typedef struct RingBuf {
  ItemType *items;
  size_t wpos;
  size_t rpos;
  size_t capacity;
} RingBuf;

RingBuf *rb_init(size_t capacity) {
  if (capacity < 2) {
    printf("invalid capacity: %zu\n", capacity);
    return NULL;
  }
  RingBuf *rb = malloc(sizeof(RingBuf));
  rb->rpos = 0;
  rb->wpos = 0;
  rb->capacity = capacity;
  rb->items = malloc(capacity * sizeof(*rb->items));
}
int rb_free(RingBuf *rb) {
  if (NULL == rb) {
    return 0;
  }
  free(rb);
  return 1;
}
int rb_empty(RingBuf *rb) {
  return rb->rpos == rb->wpos;
}
int rb_full(RingBuf *rb) {
  return (rb->wpos + 1) % rb->capacity == rb->rpos;
}
int rb_peek(RingBuf *rb) {
  if (rb_empty(rb)) {
    return ERR_EMPTY;
  }
  return rb->items[rb->rpos];
}
int rb_read(RingBuf *rb) {
  if (rb_empty(rb)) {
    return ERR_EMPTY;
  }
  int prevpos = rb->rpos;
  rb->rpos = (rb->rpos + 1) % rb->capacity;
  return rb->items[prevpos];
}
int rb_write(RingBuf *rb, ItemType item) {
  if (rb_full(rb)) {
    return 0;
  }
  rb->items[rb->wpos] = item;
  rb->wpos = (rb->wpos + 1) % rb->capacity;
  return 1;
}
int rb_count(RingBuf *rb) {
}

void test_rb_tickle(void) {
  RingBuf *rb = rb_init(8);
  if (NULL == rb) {
    return;
  }
  rb_write(rb, 1);
  rb_write(rb, 2);
  rb_write(rb, 3);
  rb_write(rb, 4);
  rb_write(rb, 5);
  rb_write(rb, 6);
  rb_write(rb, 7);
  rb_write(rb, 8);
  rb_write(rb, 9);
  rb_write(rb, 10);
  while(!rb_empty(rb)) {
    printf("%d\n", rb_read(rb));
  }
  rb_write(rb, 256);
  rb_write(rb, 512);
  rb_write(rb, 1024);
  while(!rb_empty(rb)) {
    printf("%d\n", rb_read(rb));
  }
  printf("%d\n", rb_read(rb));
}

int main(int argc, char* argv[]) {
  size_t    *items;
  test_rb_tickle();
  // printf("sizeof ptr: %u", INT32_MAX);
  return 0;
}
