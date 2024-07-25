#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char buff[256];

void usage() {
    char buff[256];
    int ret = sprintf(buff,
                      "Este programa recibe un unico argumento que es el PID "
                      "de un proceso\n");
    write(1, buff, ret);
}

int main(int argc, char **argv) {
    char buff[256];
    int ret;

    if (argc > 2) usage();

    char path[16];
    sprintf(path, "/proc/%s/stat", argv[1]);
    int fd = open(path, O_RDONLY);

    if (fd == -1)
        exit(255);
    else {
        int spaces = 0;
        int valueIndex = 0;
        char value14[128];
        char value15[128];
        char c;
        while ((read(fd, &c, 1) > 0) && spaces < 15) {
            if (c == ' ') {
                spaces++;
                if (spaces == 14 || spaces == 15) {
                    if (spaces == 14) {
                        value14[valueIndex] = '\0';
                    } else {
                        value15[valueIndex] = '\0';
                    }
                    valueIndex = 0;
                }
            } else if (spaces >= 13 && spaces <= 14) {
                if (spaces == 13) {
                    value14[valueIndex++] = c;
                } else {
                    value15[valueIndex++] = c;
                }
            }
        }
        int val14 = atoi(value14);
        int val15 = atoi(value15);
        exit(val15 + val14);
    }
}