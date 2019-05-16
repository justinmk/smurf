// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <string.h>
// #include <fcntl.h>
// #include <errno.h>
// #include <unistd.h>
// #include <stdint.h>

// void test_dup(void) {
//   /* Close stdin and dup it from stderr.  Required for GPM to work */
//   close(0);
//   int ret2 = dup(2);
//   printf("result: %d\n", ret2);

//   printf("%lu\n", sizeof(char *));
//   FILE * fdin = fdopen(0, "r");
//   if (fdin == NULL) {
//     printf("failed to open stdin: errno: %d\n", errno);
//     exit(2);
//   }

//   ssize_t ret = 0;
//   size_t bufsize = 1;
//   char buf[4096];
//   for (;; ) {
//     ret = fread(buf, sizeof(size_t), 1, fdin);
//     if (ret <= 0) {
//       break;
//     }
//     printf("read: %s\n", buf);
//   }

//   ret2 = dup(2);
//   printf("result: %d\n", ret2);
//   ret2 = dup(2);
//   printf("result: %d\n", ret2);
//   close(0);
//   ret2 = dup(2);
//   printf("result: %d\n", ret2);
// }

// int main(int argc, char **argv) {
//   test_dup();
// }

/* Output info about the default buffering parameters
 * applied by libc to stdin, stdout and stderr.
 * Note the info is sent to stderr, as redirecting it
 * makes no difference to its buffering parameters.
 * Note gnulib has fbufmode() to make this portable.
 */
#include <stdio_ext.h>
#include <unistd.h>
#include <stdlib.h>

FILE* fileno2FILE(int fileno){
    switch(fileno) {
        case 0:  return stdin;
        case 1:  return stdout;
        case 2:  return stderr;
        default: return NULL;
    }
}

const char* fileno2name(int fileno){
    switch(fileno) {
        case 0:  return "stdin";
        case 1:  return "stdout";
        case 2:  return "stderr";
        default: return NULL;
    }
}

// int main(void)
// {
//   // uint32_t *new_ScreenLinesC[6];
//   // memset(new_ScreenLinesC, 0, sizeof(new_ScreenLinesC));
//   // printf("size %zu\n", sizeof(new_ScreenLinesC));
//   // printf("size %zu\n", sizeof(uint32_t *) * 6);
//   // int b_p_scbk = 1000;
//   // int scbk_plus_10pct = (int)((double)b_p_scbk * 1.10);
//   // printf("size %d\n", scbk_plus_10pct);
//   // int a = 72;
//   // int b = a ?: -1;
//   // printf("b %d\n", b);
// }


// #include <stdio.h>
// #include <assert.h>

// int main(void)
// {
//   // int a, b, c;
//   size_t s;
//   printf("%d\n", __builtin_sub_overflow((-111) + (-113), 1, &s));
//   // printf("%d\n", __builtin_add_overflow(x1, y1, &temp));
//   // printf("%ld  %d\n", temp, z1);

//   return 0;
// }

#include <math.h>
int main(void)
{
  double d = 1.0;
  if (FP_NORMAL != __fpclassify(d)
      || !!__isnan(d)
      || !!__isinf(d)) {
    abort();
  }
  printf("ok\n");
  return 0;
}
