#include <bits/types/sigset_t.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char **aux;
char buff[256];
int seg = 0;

void max(int s) {
  if (s == SIGALRM) {
    printf("Me ha llegado el signal SIGALRM\n");
    seg += 5;
    if (fork() > 0) {
      execlp("./nproc_time_max", "./nproc_time_max", aux, (char *)NULL);
      perror("Error en el execlp");
      exit(255);
    }
  } else if (s == SIGUSR1) {
    printf("Me ha llegado el signal SIGUSR1\n");
    int ret = sprintf(buff, "Llevo %d segundos en ejecucion", seg);
    write(1, buff, ret);
    exit(1);
  }
}

void usage() {
  perror("Este programa necesita recibir como minimo el PID de un proceso\n");
  exit(255);
}

int main(int argc, char **argv) {
  if (argc < 2)
    usage();

  struct sigaction sa;
  aux = argv;
  printf("%s", aux[1]);
  sa.sa_handler = &max;
  sa.sa_flags = 0;
  sigfillset(&sa.sa_mask);

  if (sigaction(SIGALRM, &sa, NULL) < 0) {
    perror("Error en el sigaction(SIGALRM)");
    exit(255);
  }
  if (sigaction(SIGUSR1, &sa, NULL) < 0) {
    perror("Error en el sigaction(SIGUSR1)");
    exit(255);
  }

  // Implementamos la espera bloqueante
  while (1) {
    alarm(5);
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigdelset(&mask, SIGINT);
    sigsuspend(&mask);
  }
}
