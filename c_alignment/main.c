#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
// #include <math.h>

int main(void)
{
  int64_t a = 42;
  printf("%ld\n", a);
  printf("%d\n", (int32_t)a);
  printf("%u\n", (uint32_t)a);

  printf("%d\n", (int32_t)((int32_t *)(&a))[0]);
  printf("%d\n", (int32_t)((int32_t *)(&a))[1]);
  return 0;
}

