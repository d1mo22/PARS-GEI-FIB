#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int recibido = 0;

void usage() {
  perror("Este programa tiene que tener entre 1 y 2 parametros y el segundo "
         "parametro tiene que ser 'c' o 'i'\n");
  exit(5);
}

void sig(int s) {
  if (s == SIGUSR1) {
    char buff[256];
    recibido = 1;
    int ret = sprintf(buff, "El proceso %d comienza\n", getpid());
    write(1, buff, ret);
  }
}

int buscar_format(int argc, char **argv) {
  if (argc < 3) {
    if (strcmp(argv[0], "./p1-char.exe") == 0)
      return 0;
    if (strcmp(argv[0], "./p1-integer.exe") == 0)
      return 1;
  } else {
    if (strcmp(argv[2], "c") == 0)
      return 0;
    if (strcmp(argv[2], "i") == 0)
      return 1;
  }
  return -1;
}
// El primer parametro siempre es un numero, este indica la cantidad
// de elementos que se escribira en formato interno
// Si tiene un segundo parametro de entrada este inidca el tie de
// elementos que escribira
// Tiene los posibles valores c (char) o i (int);
int main(int argc, char **argv) {
  if (argc < 2 || argc > 3)
    usage();

  // Formato = 1 --> int
  // Formato = 0 --> char
  int formato = buscar_format(argc, argv);

  if (formato == -1)
    usage();

  int ret;
  char buff[256];
  struct sigaction sa;
  sigfillset(&sa.sa_mask);
  sa.sa_handler = &sig;
  sa.sa_flags = 0;

  if (sigaction(SIGUSR1, &sa, NULL) < 0) {
    perror("Error en el sigaction(SIGUSR1)\n");
    exit(5);
  }

  while (!recibido)
    ;
  int limite = atoi(argv[1]);
  int i;
  for (i = 0; i < limite; ++i) {
    if (formato) {
      ret = sprintf(buff, "%d\n", i);
    } else {
      ret = sprintf(buff, "%c\n", i);
    }
    write(10, buff, ret);
  }
  ret = sprintf(buff, "El proceso %d ha terminado\n", getpid());
  write(1, buff, ret);
  exit(i);
}
