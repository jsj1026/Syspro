#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int pid;

void alarmHandler() {
    printf("[alarm] child process %d time out\n", pid);
    kill(pid, SIGKILL);  // SIGINT 대신 SIGKILL을 사용하여 강제 종료
}

/* 명령줄 인수로 받은 명령어 실행에 제한 시간을 둔다. */
int main(int argc, char *argv[]) {
    int child, status, limit;

    signal(SIGALRM, alarmHandler);
    sscanf(argv[1], "%d", &limit);
    alarm(limit);
    pid = fork();
    
    if (pid == 0) {
        execvp(argv[2], &argv[2]);
        fprintf(stderr, "%s: Cannot execute\n", argv[2]);  // argv[1]이 아닌 argv[2]로 수정
    } else if (pid > 0) {  // fork 성공 여부 확인
        child = wait(&status);
        printf("[%d] child process %d exit\n", getpid(), pid);
    } else {
        perror("fork");
        return 1;  // fork 실패 시 프로그램 종료
    }
    return 0;
}
