// Write a C program which creates a child process and child process catches a signal
// SIGHUP, SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT
// signal after every 3 seconds, at the end of 15 second parent send SIGQUIT signal to
// child and child terminates by displaying message "My Papa has Killed me!!!”

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

// Signal handler function for the child process
void child_signal_handler(int signum) {
    switch (signum) {
        case SIGHUP:
            printf("Child process received SIGHUP signal\n");
            break;
        case SIGINT:
            printf("Child process received SIGINT signal\n");
            break;
        case SIGQUIT:
            printf("My Papa has Killed me!!!\n");
            exit(EXIT_SUCCESS);
            break;
    }
}

int main() {
    pid_t child_pid;

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Register signal handlers for SIGHUP, SIGINT, and SIGQUIT
        signal(SIGHUP, child_signal_handler);
        signal(SIGINT, child_signal_handler);
        signal(SIGQUIT, child_signal_handler);

        // Infinite loop to keep the child process running
        while (1) {
            // Do nothing, waiting for signals
        }
    } else {
        // Parent process

        // Send SIGHUP or SIGINT every 3 seconds for a total of 15 seconds
        for (int i = 0; i < 5; ++i) {
            sleep(3);
            if (i % 2 == 0) {
                kill(child_pid, SIGHUP);
            } else {
                kill(child_pid, SIGINT);
            }
        }

        // Send SIGQUIT after 15 seconds
        sleep(3);
        kill(child_pid, SIGQUIT);

        // Wait for the child process to complete
        wait(NULL);
    }

    return 0;
}
