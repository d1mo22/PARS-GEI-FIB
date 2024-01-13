#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int recibido = 0;

void usage() {
  perror("Este programa espera parámetros de entrada en forma de duplas X Y, "
         "donde X es un número e Y es un carácter (‘c’ o ‘i’)\n");
  exit(5);
}

void sig(int s) {
  if (s == SIGALRM) {
    recibido = 1;
  }
}

int main(int argc, char **argv) {
  if (argc < 2)
    usage();

  mknod("MYPIPE", S_IFIFO | 0666, 0);
  if (errno != EEXIST) {
    perror("Error al crear la pipe\n");
    exit(5);
  }

  struct sigaction sa;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = &sig;

  if (sigaction(SIGALRM, &sa, NULL) < 0) {
    perror("Error en el sigaction\n");
    exit(5);
  }

  int ret;
  int hijos = (argc - 1) / 2;
  int format;
  char buff[256];
  for (int i = 2; i < hijos; i += 2) {
    int n = atoi(argv[i - 1]);

    if (strcmp(argv[i], "c") == 0)
      format = 0;
    else
      format = 1;

    ret = fork();
    if (ret == 0) { // HIJO
      int fd = open("MYPIPE", O_WRONLY);
      if (fd == -1) {
        perror("Error en el open\n");
        exit(5);
      }
      dup2(fd, 10);

      execlp("./p1", "./p1", argv[i - 1], argv[i], (char *)NULL);
      perror("Error en el execlp\n");
      exit(5);
    }

    else { // PADRE
      alarm(2);
      while (!recibido)
        ;
      kill(ret, SIGUSR1);
      int fd = open("MYPIPE", O_RDONLY);
      char salida[64];
      sprintf(salida, "salida-%d.dat", ret);

      if (format) { // Integer
        int *p;
        p = malloc(n * 4);
        int x, i;
        while (read(fd, &x, 4) > 0) {
          p[i] = x;
          ++i;
        }
        // Esperar al hijo

        int fd_w = open(salida, O_WRONLY | O_TRUNC | O_CREAT, 0660);
        write(fd_w, p, n * 4);
        free(p);

      } else { // Char
        char *c;
        c = malloc(n);
        char x;
        int i;
        while (read(fd, &x, 1) > 0) {
          c[i] = x;
          ++i;
        }
        // Esperar al hijo
        int fd_w = open(salida, O_WRONLY | O_TRUNC | O_CREAT, 0660);
        write(fd_w, c, n);
        free(c);
      }
    }
  }
  sprintf(buff, "Final del proceso principal\n");
  write(1, buff, strlen(buff));
}
