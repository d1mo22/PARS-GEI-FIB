#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int sigchild_recibido = 0;
int pid_h;

void hago_algo_de_trabajo() {
    int sum;
    for (int i = 0; i < 10000; ++i) {
        if (i%2) sum++;
        else --sum;
    }
}

void trat_sigalrm(int signum) {
    char buff[128];
    if(!sigchild_recibido) kill(pid_h, SIGKILL);
    strcpy(buff, "TIMEOUT!");
    write(1, buff, strlen(buff));
    exit(1);
}

void trat_sigchild(int signum) {
    sigchild_recibido = 1;
}

void main(int argc, char** argv) {
    int ret, n;
    int nhijos = 0;
    char buff[128];
    struct sigaction trat;
    trat.sa_flags = 0;
    sigemptyset(&trat.sa_mask);
    trat.sa_handler = trat_sigchild;
    sigaction(SIGCHLD, &trat, NULL);

    n = atoi(argv[1]);
    if (n > 0) {
        pid_h = fork();
        if (pid_h == 0) {
            n--;
            trat.sa_flags = 0;
            sigemptyset(&trat.sa_mask);
            trat.sa_handler = trat_sigalrm;
            sigaction(SIGALRM, &trat, NULL);
            sprintf(buff, "%d", n);
            execlp("./temp", "temp", buff, (char*)0);
        }
        strcpy(buff, "Voy a trabajar \n");
        write(1, buff, strlen(buff));
        alarm(10);
        hago_algo_de_trabajo();
        alarm(0);
        while ((ret=waitpid(-1, NULL, 0)) > 0) ++nhijos;
        sprintf(buff, "Fin de ejecucion. Hijos esperados: %d\n", nhijos);
        write(1, buff, strlen(buff));
    }
    else {
        strcpy(buff, "Voy a trabajar \n");
        write(1, buff, strlen(buff));
        alarm(10);
        hago_algo_de_trabajo();
        alarm(0);
        strcpy(buff, "Fin ejecucion\n");
        write(1, buff, strlen(buff));
    }
}