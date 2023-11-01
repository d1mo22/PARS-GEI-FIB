#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int pid;
char buff[256];

void error_y_exit(char* msg) {
    perror(msg);
    exit(0);
}

void trat_signal (int s) {
    if (s == SIGUSR1) {
        sprintf(buff, "SIGNAL recibido %d\n", s);
        write(1, buff, strlen(buff));
    }
    else {
        sprintf(buff, "SIGNAL recibido %d\n", s);
        write(1, buff, strlen(buff));
        if (pid != 0) kill (SIGUSR2, pid);
        exit(0);
    }
    
}

int main(int argc, char** argv) {
    int ret;
    pid = atoi(argv[1]);
    char* palabra = argv[2];
    char* fichero = argv[3];

    sigset_t mask;
    sigemptyset(&mask);

    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_mask = mask;
    sa.sa_handler = trat_signal;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    sigfillset(&mask);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGUSR2);
    sigdelset(&mask, SIGINT);
    sigsuspend(&mask);

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
            if (pid != 0) {
                if (exit_status == 1)  {
                    kill (pid, SIGUSR1);
                }
                else if (exit_status == 0){
                    kill(pid, SIGUSR2);
                }
            }
        }
        else {
            error_y_exit("El hijo no ha terminado normalmente");
        }
    }
    exit(0);
}