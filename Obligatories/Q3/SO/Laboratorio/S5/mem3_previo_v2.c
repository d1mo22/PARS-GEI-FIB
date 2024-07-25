#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include<unistd.h>

#define REGION_SIZE	4096

void trat_sig(int s) {
  perror("Has accedido a una posicion de memoria no permitida\n");
  exit(2);
}

int *p;

int main (int argc, char *argv[]) {
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = trat_sig;
  sigaction(SIGSEGV, &sa, NULL);

  char buff[256];

  sprintf (buff, "Addresses:\n");
  write (1, buff, strlen (buff));

  sprintf (buff, "\tp: %p\n", &p);
  write (1, buff, strlen (buff));

  *p = 5;

  sprintf (buff, "\tp Address: %p, p value: %p, *p: %d\n", &p, p, *p);
  write (1, buff, strlen (buff));

  exit (0);

}
