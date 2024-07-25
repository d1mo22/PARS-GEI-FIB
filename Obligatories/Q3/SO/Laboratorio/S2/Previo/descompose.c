#include <stdio.h>
#include <string.h>
#define STDOUT 1

int main(int argc, char* argv[]){
    int N;
    N = atoi(argv[1]);
    int h = N/3600;
    int m = (N%3600)/60;
    int s = N%60;
    char buff[128];
    sprintf(buff, "%d hours, %d minutes and %d seconds\n", h, m, s);
    write(STDOUT, buff, strlen(buff));
}