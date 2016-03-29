#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

uint32_t oat_hash(void *key, int len) {
  char *p = key;
  uint32_t h = 0;
  int i;
  for (i = 0; i < len; i++) {
    h += p[i];
    h ^= (h << 10);
    h ^= (h >> 6);
  }
  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);

  return h;
}

struct Foo {
  // union {
  uint32_t data1;
  uint32_t data2;
  // };
} typedef Foo;

int main2(int argc, char *argv[]) {
  uint32_t h = oat_hash(argv[1], strlen(argv[1]));
  printf("key: %s hashed: %"PRIu32"\n", argv[1], h);
}
int main3(int argc, char *argv[]) {
//   int a=0x10000000;
//   char b;
//   b = *((int *)&a);
//   char *noeol = malloc(10);
//   char *noeol2 = malloc(40*szeof(char));
//   *noeol = 'b';
//   noeol2 = "cccc";
//   memset(noeol+1, 'c', 4*sizeof(char));
//   // printf("%#x\n", b);
//   printf("%d\n", strcmp(noeol2,noeol));
//   printf("%s\n", noeol);
// #ifdef DEBUG
//   printf("debug", b);
// #endif
//   printf("\n======================\n");

  Foo foo;
  // printf("data: %"PRIu64, foo.data1));
  foo.data1 = 0x01;
  foo.data2 = 0x01;
  void * zub = (void *)&foo;
  printf("data[...]: %"PRIu64"\n", *((uint64_t *)zub));
  // uint64_t l1 = 0x00ff00ff;
  // uint8_t s1 = l1;
  // memset(&l1, 1, 2);
  // printf("l1: %"PRIu64" s1: %"PRIu64"\n", l1, s1);
  return 0;
}
int main(int argc, char *argv[]) {
  char* foo = "";
  if (*foo) {
    printf("yes\n");
  }
  else
    printf("no\n");
}
