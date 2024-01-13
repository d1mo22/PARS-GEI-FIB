#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void usage() {
  perror("Este programa necesita recibir 2 parametros\n");
  exit(5);
}

void RSI(int s) {
  if (s == SIGALRM) {
    char buff[256];
    int ret = sprintf(buff, "Limite tiempo\n");
    write(1, buff, ret);
    exit(255);
  }
}

int main(int argc, char **argv) {
  if (argc < 4)
    usage();

  sigset_t mask;
  sigfillset(&mask);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  struct sigaction sa;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = &RSI;
  if (sigaction(SIGALRM, &sa, NULL) < 0) {
    perror("Error en el sigaction\n");
    exit(255);
  }
  sigprocmask(SIG_UNBLOCK, &mask, NULL);

  int n = atoi(argv[1]);
  int ret;
  int seed = atoi(argv[2]);
  alarm(atoi(argv[3]));

  for (int i = 0; i < n; ++i) {
    ret = fork();
    if (ret == -1) {
      perror("Error en el fork\n");
      exit(255);
    } else if (ret == 0) {
      char semilla[4];
      sprintf(semilla, "%d", seed);
      execlp("./dummy", "./dummy", semilla, (char *)NULL);
      perror("Error en el execlp\n");
      exit(255);

    } else {
      int status;
      waitpid(ret, &status, 0);
      if (WIFEXITED(status)) {
        seed += WEXITSTATUS(status);
      }
    }
  }
  char buff[256];
  ret = sprintf(buff, "El total es %d\n", seed);
  write(1, buff, ret);
}
