// Write a C program which create a child process which catch a signal sighup, sigint
// and sigquit. The Parent process send a sighup or sigint signal after every 3 seconds, at
// the end of 30 second parent send sigquit signal to child and child terminates my
// displaying message “My DADDY has Killed me!!!”.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

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
            printf("My DADDY has Killed me!!!\n");
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

        // Send SIGHUP or SIGINT every 3 seconds for a total of 30 seconds
        for (int i = 0; i < 10; ++i) {
            sleep(3);
            if (i % 2 == 0) {
                kill(child_pid, SIGHUP);
            } else {
                kill(child_pid, SIGINT);
            }
        }

        // Send SIGQUIT after 30 seconds
        sleep(3);
        kill(child_pid, SIGQUIT);

        // Wait for the child process to complete
        wait(NULL);
    }

    return 0;
}
