// Write a C program that illustrates suspending and resuming processes using signals.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function for suspending the child process
void sigusr1_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Child process suspended.\n");
        pause(); // Wait until a signal is received
        printf("Child process resumed.\n");
    }
}

// Signal handler function for resuming the child process
void sigusr2_handler(int signum) {
    if (signum == SIGUSR2) {
        // No specific action needed for resuming
        printf("Parent process resumed child.\n");
    }
}

int main() {
    pid_t child_pid;

    // Register signal handlers for SIGUSR1 and SIGUSR2 in the parent process
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        while (1) {
            // Child process logic
            printf("Child process is running.\n");
            sleep(1);
        }

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Wait for a while to ensure the child process is running
        sleep(3);

        // Suspend the child process by sending SIGUSR1
        printf("Parent process sending SIGUSR1 to suspend the child process.\n");
        kill(child_pid, SIGUSR1);

        // Wait for a while to demonstrate the child is suspended
        sleep(3);

        // Resume the child process by sending SIGUSR2
        printf("Parent process sending SIGUSR2 to resume the child process.\n");
        kill(child_pid, SIGUSR2);

        // Wait for the child process to complete
        wait(NULL);

        printf("Parent process exiting.\n");
    }

    return 0;
}