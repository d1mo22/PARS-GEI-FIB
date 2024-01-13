#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void usage() {
  perror("Este programa necesita recibir 2 parametros\n");
  exit(5);
}

int main(int argc, char **argv) {
  if (argc < 3)
    usage();
  int n = atoi(argv[1]);
  int ret;
  int seed = atoi(argv[2]);
  for (int i = 0; i < n; ++i) {
    ret = fork();
    if (ret == 0) {

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
