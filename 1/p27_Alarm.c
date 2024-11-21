// Write a C program to send SIGALRM signal by child process to parent process and
// parent process make a provision to catch the signal and display alarm is fired.(Use
// Kill, fork, signal and sleep system call)


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler function for SIGALRM
void sigalrm_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Alarm is fired!\n");
    }
}

int main() {
    pid_t child_pid;

    // Register signal handler for SIGALRM in the parent process
    signal(SIGALRM, sigalrm_handler);

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Sleep for a while to allow parent to set up signal handler
        sleep(2);

        // Send SIGALRM signal to the parent process
        kill(getppid(), SIGALRM);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Wait for the child process to complete
        wait(NULL);

        // Parent process continues to execute
        printf("Parent process continuing...\n");

        // Sleep for a while to ensure the child has sent the signal
        sleep(1);

        // Continue with the parent process logic

        return 0;
    }
}
