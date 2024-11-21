// Write a C program which creates a child process to run linux/ unix command or any
// user defined program. The parent process set the signal handler for death of child
// signal and Alarm signal. If a child process does not complete its execution in 5
// second then parent process kills child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function for the death of the child (SIGCHLD)
void sigchld_handler(int signum) {
    if (signum == SIGCHLD) {
        printf("Child process has terminated.\n");
        exit(EXIT_SUCCESS);
    }
}

// Signal handler function for the alarm signal (SIGALRM)
void sigalrm_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Timeout: Child process did not complete in 5 seconds. Killing the child.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    pid_t child_pid;

    // Register signal handlers for SIGCHLD and SIGALRM in the parent process
    signal(SIGCHLD, sigchld_handler);
    signal(SIGALRM, sigalrm_handler);

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Simulate some work in the child process
        sleep(10);

        printf("Child process completed.\n");

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Set an alarm to trigger SIGALRM after 5 seconds
        alarm(5);

        // Wait for the child process to complete
        wait(NULL);

        // Cancel the alarm
        alarm(0);

        printf("Parent process exiting.\n");
    }

    return 0;
}
