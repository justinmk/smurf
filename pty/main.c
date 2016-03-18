#include <stdio.h>
#include <fcntl.h>

//http://man7.org/tlpi/code/online/dist/pty/pty_master_open.c.html
int main(int argc, char* argv[]) {
  int fd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
  int fd2 = open("/dev/ptmx", O_RDWR | O_NOCTTY);
  // close(fd);
  // close(fd2);
  printf("ptmx fd: %d\n", fd);
  printf("ptmx fd2: %d\n", fd2);
  printf("ptmx fd2: %d\n", open("/dev/ptmx", O_RDWR | O_NOCTTY));
  sleep(50000);
  return 0;
}
