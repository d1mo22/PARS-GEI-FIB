#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mis_funciones.h"

void usage(){
	char buf[500];
	sprintf(buf,"Usage: words arg1..argn\nEste programa escribe por su salida la cantidad de palabras de una frase que recibe\n");
	write(1,buf,strlen(buf));
}

int main (int argc, char *argv[]) {
	if (argc == 1){
	usage();
	return 0;
	}
	char buf[80]; 
	int c = 0;
	for (int i = 1; i < strlen(argv[1]); i++) {
      		if (argv[1][i] == ' ' || argv[1][i+1] == '\0' ||  argv[1][i] == ',' || argv[1][i] == '.') ++c;
	}
	sprintf (buf, "%d palabras\n", c);
	write (1, buf, strlen (buf));
	return 0;
}
