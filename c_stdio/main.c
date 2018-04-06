#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void test_dup(void) {
  /* Close stdin and dup it from stderr.  Required for GPM to work */
  close(0);
  int ret2 = dup(2);
  printf("result: %d\n", ret2);

  printf("%lu\n", sizeof(char *));
  FILE * fdin = fdopen(0, "r");
  if (fdin == NULL) {
    printf("failed to open stdin: errno: %d\n", errno);
    exit(2);
  }

  ssize_t ret = 0;
  size_t bufsize = 1;
  char buf[4096];
  for (;; ) {
    ret = fread(buf, sizeof(size_t), 1, fdin);
    if (ret <= 0) {
      break;
    }
    printf("read: %s\n", buf);
  }

  ret2 = dup(2);
  printf("result: %d\n", ret2);
  ret2 = dup(2);
  printf("result: %d\n", ret2);
  close(0);
  ret2 = dup(2);
  printf("result: %d\n", ret2);
}

int main(int argc, char **argv) {
  test_dup();
}
