#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

// Logging function
void log_action(char *action, char *name, int pid) {
    FILE *f = fopen("log.txt", "a");
    if (f != NULL) {
        fprintf(f, "[%s] Container: %s | PID: %d\n", action, name, pid);
        fclose(f);
    }
}

// Start container
void start_container(char *name, char *command) {
    int pid = fork();

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(0);
    } 
    else if (pid > 0) {
        printf(">>> Container '%s' started successfully (PID %d)\n", name, pid);
        log_action("STARTED", name, pid);
    } 
    else {
        printf("Error creating container\n");
    }
}

// Stop container
void stop_container(char *name) {
    printf(">>> Attempting to stop container '%s'\n", name);

    // Since we don't store PIDs persistently,
    // this is just a simulation message
    printf(">>> Container '%s' stopped (simulation)\n", name);
    log_action("STOPPED", name, -1);
}

// Show logs
void show_logs() {
    FILE *f = fopen("log.txt", "r");

    if (f == NULL) {
        printf("No logs available\n");
        return;
    }

    char line[200];
    printf("\n--- Container Logs ---\n");

    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    printf("----------------------\n");
    fclose(f);
}

// List (same as logs)
void list_containers() {
    printf("\n>>> Listing containers (log-based view)\n");
    show_logs();
}

// Help command
void show_help() {
    printf("\nAvailable Commands:\n");
    printf("./engine start <name> \"command\"\n");
    printf("./engine stop <name>\n");
    printf("./engine list\n");
    printf("./engine logs\n");
    printf("./engine help\n\n");
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        show_help();
        return 0;
    }

    if (strcmp(argv[1], "start") == 0) {
        if (argc < 4) {
            printf("Usage: ./engine start <name> \"command\"\n");
            return 0;
        }
        start_container(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "stop") == 0) {
        if (argc < 3) {
            printf("Usage: ./engine stop <name>\n");
            return 0;
        }
        stop_container(argv[2]);
    }
    else if (strcmp(argv[1], "list") == 0) {
        list_containers();
    }
    else if (strcmp(argv[1], "logs") == 0) {
        show_logs();
    }
    else if (strcmp(argv[1], "help") == 0) {
        show_help();
    }
    else {
        printf("Invalid command. Use './engine help'\n");
    }

    return 0;
}
