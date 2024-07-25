#include <stdio.h>
#include <string.h>
#include <unistd.h>

void usage(){
	char buf[120];
	int len = sprintf(buf, "Usage:listaParametros arg1 [arg2..argn] \nEste programa escribe por su salida la lista de argumentos que recibe \n");
	write(1, buf, len);
}

int main(int argc,char *argv[])
{
	if (argc == 1) usage();
	else {
		char buf[80];
		for (int i=0;i<argc;i++){
			if (i==0){
				sprintf(buf,"El argumento %d es %s (es el nombre del ejecutable)\n",i,argv[i]);
			}
			else{
				sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
			}
			write(1,buf,strlen(buf));
		}
	}
	
	return 0;
}
