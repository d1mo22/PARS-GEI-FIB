#include <unistd.h>
#include <stdio.h>

int main () {
    int numero, fd;
    char* buff;
    read(0, &numero, sizeof(int));
    fd = sprintf(buff, "%d\n", numero);
    write (1, buff, fd);
}
