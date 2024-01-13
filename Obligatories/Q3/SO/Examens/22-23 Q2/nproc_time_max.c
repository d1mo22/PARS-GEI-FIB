#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    char buff[256];
    int fd_p[2] = mknod("MIPIPE", ) for (int i = 1; i < argc; ++i) {
        int ret = fork();
        if (ret == 0) {  // Este es el proceso hijo
            execlp("./proc_time", "./proc_time", argv[i], (char*)NULL);
            perror("execlp");  // Solo se llega aquí si execlp falla
            exit(255);
        } else {  // Este es el proceso padre
            int status;
            waitpid(ret, &status, 0);
            if (WIFEXITED(status)) {
                printf("Tiempo en ejecuccion: %d\n", WEXITSTATUS(status));
            }
        }
    }
}