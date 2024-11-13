#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void print_env_var(const char *var_name) {
    if (var_name) {
        char *value = getenv(var_name);
        if (value) {
            printf("Environment variable %s: %s\n", var_name, value);
        } else {
            printf("Environment variable %s is not set.\n", var_name);
        }
    } else {
        extern char **environ;
        for (char **env = environ; *env; env++) {
            printf("%s\n", *env);
        }
    }
}

void print_user_ids() {
    printf("Real User ID: %d\n", getuid());
    printf("Effective User ID: %d\n", geteuid());
}

void print_group_ids() {
    printf("Real Group ID: %d\n", getgid());
    printf("Effective Group ID: %d\n", getegid());
}

void print_process_id() {
    printf("Process ID: %d\n", getpid());
}

void print_parent_process_id() {
    printf("Parent Process ID: %d\n", getppid());
}

int main(int argc, char *argv[]) {
    int opt;
    const char *env_var_name = NULL;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s [-e] [environment_variable_name] [-u] [-g] [-i] [-p]\n", argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "eugip")) != -1) {
        switch (opt) {
            case 'e':
                if (optind < argc && argv[optind][0] != '-') {
                    env_var_name = argv[optind];
                    optind++;
                }
                print_env_var(env_var_name);
                break;
            case 'u':
                print_user_ids();
                break;
            case 'g':
                print_group_ids();
                break;
            case 'i':
                print_process_id();
                break;
            case 'p':
                print_parent_process_id();
                break;
            default:
                fprintf(stderr, "Usage: %s [-e] [environment_variable_name] [-u] [-g] [-i] [-p]\n", argv[0]);
                return 1;
        }
    }

    return 0;
}
