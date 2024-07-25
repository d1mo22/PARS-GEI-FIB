#include "mis_funciones.h"


int main(int argc, char* argv[]){
    char buff[80];
    int resultat = 0;
    if (argc < 3) {
        usage();
        return 0;
    } 
    for (int i = 1; i < argc; ++i) {
        if (esNumero(argv[i]) == 0) {
            sprintf(buff, "Error: el parametro %s no es un numero \n", argv[i]);
            write (1, buff, strlen(buff));
            return 0;
        } 
        else resultat += mi_atoi(argv[i]);
        
    }
    sprintf(buff, "La suma es %d\n", resultat);
    write(1, buff, strlen(buff));
    return 0;
}