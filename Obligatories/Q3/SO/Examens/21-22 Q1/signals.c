#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

char buff[256];
int recibido = 0;
int hijos[10];
int hijos_totales;
int turno = 1;

void usage() {
    sprintf(buff, "El programa necesita entre 1 y 10 nombres de fichero\n");
    exit(1);
}

void error_y_exit(char* msg) {
    perror(msg);
    exit(1);
}

void trat_sig(int s) {
    if (s == SIGUSR1) recibido = 1;
    else if (s == SIGINT)  {
        sprintf(buff, "Se ha salido de la espera");
        kill(hijos[turno], SIGUSR1);
        --hijos_totales;
    }
    else if (s == SIGALRM) {
        for (int i = 0; i < hijos_totales; ++i) {
            kill(hijos[i], SIGKILL);
        }
        hijos_totales = 0;
    }
}

int main(int argc, char** argv) {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = trat_sig;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    hijos_totales = argc - 1;
    if (argc < 2 || argc > 11) usage();
    int ret;
    for (int i = 1; i < argc; ++i) {
        ret = fork();
        if (ret < 0) error_y_exit("Error en el fork");
        else if (ret == 0) {
            struct sigaction sa;
            sigemptyset(&sa.sa_mask);
            sa.sa_handler = trat_sig;
            sa.sa_flags = 0;
            sigaction(SIGUSR1, &sa, NULL);
            while(!recibido);
            sprintf(buff, "El programa que tengo que tratar es %s\n", argv[i]);
            write(1,buff, strlen(buff));
            exit(i);
        }
        else {
            hijos[i] = ret;
        }
    }

    sigaction(SIGALRM, &sa, NULL);
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    while (hijos_totales > 0) {
        alarm(2);
        sigsuspend(&mask);
        ++turno;
    }

    int status, pid;
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            sprintf(buff, "El proceso con PID: %d ha muerto por exit con codigo: %d\n", pid, WEXITSTATUS(status));
            write(1, buff, strlen(buff));
        }
        else if (WIFSIGNALED(status)) {
            sprintf(buff, "El proceso con PID: %d ha muerto por signal con codigo: %d\n", pid, WTERMSIG(status));
            write(1, buff, strlen(buff));
        }
        else error_y_exit("Mort per causa desconeguda");
    }
}