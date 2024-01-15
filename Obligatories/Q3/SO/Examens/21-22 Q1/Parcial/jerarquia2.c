#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char buff [256];
int status;

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
        char* fichero = argv[i];
        ret = fork();
        if (ret < 0) error_y_exit("Error en el fork");
        else if (ret == 0) {
            sprintf(buff, "El programa que tengo que tratar es %s\n", fichero);
            write(1,buff, strlen(buff));

            for (int i = 0; i < 3; ++i) {
                sprintf(buff, "%s_sin_repes", fichero);
                ret = fork();
                if (ret < 0) error_y_exit("Error en el fork");

                else if (ret == 0) {
                    if (i == 0) {
                        execlp("wc", "wc", "-l", fichero, (char*)NULL);
                        error_y_exit("Error execlp");
                    }
                    else if (i == 1) {
                        execlp("sort", "sort", "-u", fichero, "-o", buff, (char*)NULL);
                        error_y_exit("Error execlp");
                    } 
                    else {
                        execlp("wc", "wc", "-l", buff, (char*)NULL);
                        error_y_exit("Error execlp");
                    }
                }
                else {
                    waitpid(ret, &status, 0);
                }
            }
            exit(0);
        }
        else {
            hijos[i] = ret;
        }
    }
    for (int i = 1; i < argc; ++i){
        waitpid(hijos[i], &status, 0);
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