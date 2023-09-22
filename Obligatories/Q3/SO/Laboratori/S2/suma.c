#include <stdio.h>
#include <stdlib.h>
#define STDOUT 1

int main(int argc, char *argv[]) {
    int x, y;
    char buff[128];
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    int s = x + y;
    sprintf(buff, "%d\n", s);
    write(STDOUT, buff, strlen(buff));
}