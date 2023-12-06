#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXARG 10
#define MAXLINE 100

void execute_command(char *args[], int background, char *input_file, char *output_file) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { 

        if (input_file != NULL) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }


        if (output_file != NULL) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }


        if (execvp(args[0], args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else { 
        if (!background) {
       
           waitpid(pid, NULL, 0);
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
        char *input_file = NULL;
        char *output_file = NULL;

        for (int i = 0; i < arg_count; i++) {
            if (strcmp(args[i], ";") == 0) {

                args[i] = NULL;
                execute_command(args, background, input_file, output_file);
                arg_count = 0;
            } else if (strcmp(args[i], "&") == 0) {
                background = 1;
                args[i] = NULL;
            } else if (strcmp(args[i], "<") == 0) {
                if (i + 1 < arg_count) {
                    input_file = args[i + 1];
                    args[i] = NULL;
                    args[i + 1] = NULL;
                } else {
                    fprintf(stderr, "Error: Missing input file after <\n");
                    break;
                }
            } else if (strcmp(args[i], ">") == 0) {
                if (i + 1 < arg_count) {
                    output_file = args[i + 1];
                    args[i] = NULL;
                    args[i + 1] = NULL;
                } else {
                    fprintf(stderr, "Error: Missing output file after >\n");
                    break;
                }
            }
        }


        if (arg_count > 0) {
            execute_command(args, background, input_file, output_file);
        }
    }

    return 0;
}
