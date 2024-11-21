// Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the appropriate message and exits on pressing ctrl-c again
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Variable to count the number of times Ctrl-C is pressed
int ctrl_c_count = 0;

// Signal handler function
void sigint_handler(int signum) {
    if (signum == SIGINT) {
        ctrl_c_count++;

        if (ctrl_c_count == 1) {
            printf("Ctrl-C pressed. Press again to exit.\n");
        } else {
            printf("Exiting program.\n");
            exit(EXIT_SUCCESS);
        }
    }
}

int main() {
    // Register the signal handler for SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl-C to see the message.\n");

    // Infinite loop to keep the program running
    while (1) {
        // Do nothing, waiting for Ctrl-C
    }

    return 0;
}
