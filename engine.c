#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t child_pid = -1;
char container_name[100];

void log_event(const char *status) {
    FILE *f = fopen("log.txt", "a");
    if (f) {
        fprintf(f, "[%s] Container: %s | PID: %d\n", status, container_name, child_pid);
        fclose(f);
    }
}

void handle_sigint(int sig) {
    if (child_pid > 0) {
        kill(child_pid, SIGKILL);
        printf("\nContainer stopped\n");

        log_event("STOPPED");
    }
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: ./engine start <name> <command>\n");
        return 1;
    }

    signal(SIGINT, handle_sigint);

    if (strcmp(argv[1], "start") == 0) {
        strcpy(container_name, argv[2]);

        printf("Starting container %s\n", container_name);

        child_pid = fork();

        if (child_pid == 0) {
            // child process
            execl("/bin/sh", "sh", "-c", argv[3], NULL);
            exit(1);
        } 
        else if (child_pid > 0) {
            // parent process
            log_event("STARTED");
            wait(NULL);
            log_event("STOPPED");
        } 
        else {
            perror("fork failed");
        }
    }

    return 0;
}
