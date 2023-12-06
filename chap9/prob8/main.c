#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXARG 10
#define MAXLINE 100

void execute_command(char *args[], int background) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 
    
        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else { 
        if (!background) {
          
            waitpid(pid, NULL, 0);
        } else {
            printf("Background process started: %d\n", pid);
        }
    }
}

int main() {
    char *args[MAXARG];
    char input[MAXLINE];

    while (1) {
       
        printf("[Shell] ");
        fflush(stdout);


        if (fgets(input, MAXLINE, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }


        input[strcspn(input, "\n")] = '\0';

      
        char *token;
        char *saveptr;
        int arg_count = 0;

        token = strtok_r(input, " ", &saveptr);
        while (token != NULL && arg_count < MAXARG - 1) {
            args[arg_count] = token;
            arg_count++;
            token = strtok_r(NULL, " ", &saveptr);
        }


        args[arg_count] = NULL;


        int background = 0;
        if (arg_count > 0 && strcmp(args[arg_count - 1], "&") == 0) {
            background = 1;
            args[arg_count - 1] = NULL;  "
        }


        if (arg_count > 0) {
            execute_command(args, background);
        }
    }

    return 0;
}
