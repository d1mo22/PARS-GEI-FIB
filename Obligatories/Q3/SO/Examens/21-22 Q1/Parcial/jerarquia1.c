#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char buff [256];

void usage() {
    sprintf(buff, "El programa necesita entre 1 y 10 nombres de fichero\n");
    exit(1);
}

void error_y_exit(char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 11) usage();
    int hijos [argc];
    int ret;
    for (int i = 1; i < argc; ++i) {
        ret = fork();
        if (ret < 0) error_y_exit("Error en el fork");
        else if (ret == 0) {
            sprintf(buff, "El programa que tengo que tratar es %s\n", argv[i]);
            write(1,buff, strlen(buff));
            exit(i);
        }
        else {
            hijos[i] = ret;
        }
    }
    int status, pid;
    for (int i = 1; i < argc; ++i){
        pid = waitpid(hijos[i], &status, 0);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            sprintf(buff, "PID:%d con exitcode %d\n", hijos[i], exit_code);
            write(1, buff, strlen(buff));
        }
        else {
            error_y_exit("El hijo no ha terminado con exit");
        }
    }
}