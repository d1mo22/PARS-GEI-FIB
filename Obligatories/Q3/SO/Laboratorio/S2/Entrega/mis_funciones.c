#include "mis_funciones.h"

unsigned int char2int(char c) {
    return c - '0';
}

int mi_atoi(char *s) {
    int n = 0;
    int negatiu = 0;
    if (*s == '-') {
        negatiu = 1;
        ++s;
    }
    while (*s != '\0') {
        n += char2int(*s);
        n *= 10;
        ++s;
    }
    n /= 10;

    if (negatiu) return -n;
    return n;
}

int esNumero(char* str) {
    if (str == NULL) return 0;
    if (*str == '-') ++str;
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((str[i] < '0'|| str[i] > '9') || (i >= MAX_SIZE)) return 0;
    }
    return 1;
}

void usage(){
	char buf[120];
	sprintf(buf, "Usage:listaParametrosarg1 [arg2..argn] \n Este programa escribe por su salida la lista de argumentos que recibe \n ");
	write(1, buf, strlen(buf));
}