#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_environment_variable(char* env_var_name) {
    char* env_var_value = getenv(env_var_name);
    if (env_var_value) {
        printf("%s=%s\n", env_var_name, env_var_value);
    } else {
        printf("Environment variable '%s' not found.\n", env_var_name);
    }
}

void print_user_info() {
    printf("My Realistic User ID: %d\n", getuid());
    printf("My Valid User ID: %d\n", geteuid());
}

void print_group_info() {
    printf("My Realistic Group ID: %d\n", getgid());
    printf("My Valid Group ID: %d\n", getegid());
}

void print_process_info(int print_pid, int print_ppid) {
    if (print_pid) {
        printf("My Process number : %d\n", getpid());
    }

    if (print_ppid) {
        printf("my parent's process number : %d\n", getppid());
    }
}

int main(int argc, char *argv[]) {
    int opt;
    int print_pid = 0;
    int print_ppid = 0;

    while ((opt = getopt(argc, argv, "e:ugip")) != -1) {
        switch (opt) {
            case 'e':
                print_environment_variable(optarg);
                break;
            case 'u':
                print_user_info();
                break;
            case 'g':
                print_group_info();
                break;
            case 'i':
                print_pid = 1;
                break;
            case 'p':
                print_ppid = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-e ENV_VAR] [-u] [-g] [-i] [-p]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    print_process_info(print_pid, print_ppid);

    return 0;
}
