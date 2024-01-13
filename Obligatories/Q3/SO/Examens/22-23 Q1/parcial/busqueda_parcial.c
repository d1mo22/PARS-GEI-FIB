#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void error_y_exit(char* msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char** argv)  {
    char buff[256];
    int ret, pid = atoi(argv[1]);
    char* palabra = argv[2];
    char* fichero = argv[3];

    ret = fork();
    if (ret < 0) error_y_exit("error en el fork");
    //Codigo hijo
    else if (ret == 0) {
        execlp("grep", "grep", palabra, fichero, (char*)NULL);
        error_y_exit("error en el execlp");
    }
    //Codigo padre
    else {
        int status;
        waitpid(-1, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            sprintf(buff, "Termina grep palabra %s fichero %s : exit %d\n", palabra, fichero, exit_status);
            write(1, buff, strlen(buff));

        }
        else {
            error_y_exit("El hijo no ha terminado normalmente");
        }
    }
}