#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int ret, fd;
  char buff[64];
  fd = open("salida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  ret = sprintf(buff, "ABCD\n");
  write(fd, buff, ret);
}
