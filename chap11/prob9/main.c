#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void alarmHandler(int signo);


typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler) {
    struct sigaction newact, oldact;

    newact.sa_handler = handler;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;

    if (signum == SIGALRM) {
        newact.sa_flags |= SA_RESTART;  
    }

    if (sigaction(signum, &newact, &oldact) < 0) {
        return SIG_ERR;
    }

    return oldact.sa_handler;
}

int main() {
    signal(SIGALRM, alarmHandler);
    alarm(5);    
    short i = 0;
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
    printf("end\n");
}

void alarmHandler(int signo) {
    printf("Wake up\n");
    exit(0);
}
