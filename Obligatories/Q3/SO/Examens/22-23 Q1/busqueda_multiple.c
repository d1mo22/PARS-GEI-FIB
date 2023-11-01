#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int pid;
char buff[256];

void usage() {
    sprintf(buff, "Uso: ./programa <palabra> <archivos> ...\n");
    write(1, buff, strlen(buff));
    exit(1);
}

void error_y_exit(char* msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char** argv) {
    if (argc < 3 || argc > 9) usage();
    int ret, hermano_ant = 0;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    for (int i = 2; i < argc; ++i) {
        ret = fork();
        if (ret < 0) error_y_exit("error en el fork");
        else if (ret == 0) {
            sprintf(buff, "%d", hermano_ant);
            execlp("./busqueda_parcial_con_espera", "busqueda_parcial_con_espera", buff, argv[1], argv[i], (char*)NULL);
            error_y_exit("error en el execlp");
        }
        hermano_ant = ret;
    }
    kill (hermano_ant, SIGUSR1);
    int status;
    while (waitpid(-1, &status, 0) > 0);
}