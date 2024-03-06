#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char x = 0xF0;
  char buff[64];
  int ret = 0;
  ret = sprintf(buff, "%c\n", x << 4);
  write(1, buff, ret);
}
