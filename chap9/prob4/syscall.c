#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int mysystem(const char *cmdstring);

int main() {
    int status;

    if ((status = mysystem("date")) < 0)
        perror("mysystem() 오류");
    else if (WIFEXITED(status))
        printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = mysystem("hello")) < 0)
        perror("mysystem() 오류");
    else if (WIFEXITED(status))
        printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = mysystem("who; exit 44")) < 0)
        perror("mysystem() 오류");
    else if (WIFEXITED(status))
        printf("종료코드 %d\n", WEXITSTATUS(status));

    return 0;
}

int mysystem(const char *cmdstring) {
    int pid, status;

    if (cmdstring == NULL)
        return 1;

    pid = fork();

    if (pid == -1)
        return -1;

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127); /* 명령어 실행 오류 */
    }

    do {
        if (waitpid(pid, &status, 0) == -1) {
            if (errno != EINTR) /* waitpid()로부터 EINTR 오류 외 */
                return -1;
        } else
            return status;
    } while (1);
}
