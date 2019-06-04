#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int isnum(char c) {
  return c >= '0' && c <= ('0' + 9);
}
int my_pow(int base, int exponent) {
  int r = 1;
  for (int i = 1; i <= exponent; i++) {
    r = r * base;
  }
  return r;
}
int my_atoi(char *s) {
  size_t len = strlen(s);
  int digits = 0;
  // TODO:
  //    handle negative
  //    handle whitespace
  //    radix other than decimal?
  for (int i = 0; i < len && isnum(s[i]); i++) {
    digits++;
  }
  // `digits - 1` points to the least-significant digit.
  // `digits * 10` is the magnitude at that place.

  int result = 0;
  int digit = digits;  // current digit
  for (int i = 0; i < digits; i++) {
    digit--;
    int curnum = (int)s[i] - '0';
    result = result + (curnum * my_pow(10, digit));
  }
  return result;
}
// cf. https://stackoverflow.com/a/29933810
void my_itoa(int n, char *dst, size_t dstlen) {
  dst[0] = '\0';
  int r = 0;
  int denom = 1;
  int negative = n < 0;
  int i = 0;
  int j = 0;
  if (n < 0) {
    i = 1;  //
    j = 1;  // extra space for negative sign
    dst[0] = '-';
    n = -n;  // abs value
  }
  for (; i < dstlen; i++) {
    int d = (n / denom);
    r = (d % 10);
    dst[i] = (char)r + '0';
    denom = denom * 10;
    if (d == 0) {
      dst[(n == 0) ? i + 1 : i] = '\0';
      break;
    }
  }
  // reverse the string
  for (; j < i; j++) {
    char tmp = dst[i-1];
    dst[i-1] = dst[j];
    dst[j] = tmp;
    i--;
  }
}

void do_test_atoi(char *s, int expected) {
  int rv = my_atoi(s);
  if (expected != rv) {
    printf("atoi: FAIL: %d != %d\n", expected, rv);
  } else {
    printf("atoi: OK: %d = %d\n", expected, rv);
  }
}

void do_test_itoa(int n, char *expected) {
  char rv[256];
  my_itoa(n, rv, sizeof(rv));
  if (0 != strcmp(expected, rv)) {
    printf("itoa: FAIL: '%s' != '%s'\n", expected, rv);
  } else {
    printf("itoa: OK: '%s' = '%s'\n", expected, rv);
  }
}

int main(int argc, char **argv) {
  // printf("atoi('blah'): %d\n", atoi("blah"));
  do_test_atoi("78", 78);
  do_test_atoi("78999", 78999);
  do_test_atoi("17842123", 17842123);
  do_test_atoi("0", 0);
  do_test_atoi("1", 1);

  do_test_itoa(78, "78");
  do_test_itoa(78999, "78999");
  do_test_itoa(17842123, "17842123");
  do_test_itoa(0, "0");
  do_test_itoa(1, "1");
  do_test_itoa(-713, "-713");
  return 0;
}
