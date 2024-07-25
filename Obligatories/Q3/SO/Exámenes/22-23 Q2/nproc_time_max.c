#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
    char buff[256];
    int ret;
    // ret = mknod("MIPIPE", S_IFIFO | 0666, 0);
    for (int i = 1; i < argc; ++i) {
        int ret = fork();
        if (ret == 0) {  // Este es el proceso hijo
            execlp("./proc_time", "./proc_time", argv[i], (char*)NULL);
            perror("execlp");  // Solo se llega aquí si execlp falla
            exit(255);
        } else {  // Este es el proceso padre
            int status;
            waitpid(ret, &status, 0);
            if (WIFEXITED(status) != 255) {
                int time = WIFEXITED(status);
                int fd = open("./MIPIPE", O_WRONLY);
                write(fd, &time, sizeof(time));
                close(fd);
            }
        }
    }
    int fd = open("./MIPIPE", O_RDONLY);
    int max_time = 0, time;
    while (read(fd, &time, sizeof(time)) > 0) {
        if (time > max_time) max_time = time;
    }
    close(fd);
    printf("Tiempo maximo en ejecucion: %d\n", max_time);
    return 0;
}