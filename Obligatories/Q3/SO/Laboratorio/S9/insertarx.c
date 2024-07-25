#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int ret, fd;
  char c, buff[128];
  fd = open("salida.txt", O_RDWR);
  lseek(fd, -2, SEEK_END);
  ret = read(fd, &c, sizeof(char));
  lseek(fd, -1, SEEK_CUR);
  write(fd, "X", 1);
  ret = sprintf(buff, "%c\n", c);
  write(fd, buff, ret);
}
