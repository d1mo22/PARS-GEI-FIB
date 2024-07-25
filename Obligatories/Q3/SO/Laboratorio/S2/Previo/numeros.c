#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 8
#define STDOUT 1

int esNumero(char* str) {
    if (str == NULL) return 0;
    if (*str == '-')++str;
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((str[i] < '0'|| str[i] > '9') || (i >= MAX_SIZE)) return 0;
    }
    return 1;
}

int main(int argc, char* argv[]){
    char buff[80];
    for (int i = 0; i < argc; ++i) {
        if (esNumero(argv[i])) sprintf(buff, "%s es un numero \n", argv[i]);
        else sprintf(buff, "%s no es un numero\n", argv[i]);
        write(STDOUT, buff, strlen(buff));
    }
    return 0;
}