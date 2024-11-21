// Write a C program to create „n‟ child processes. When all „n‟ child processes terminates, Display total cumulative time children spent in user and kernel mode.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_children>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; ++i) {
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            printf("Child %d (PID: %d) is executing...\n", i+1, getpid());
            sleep(1); // Simulating some work in the child process
            exit(EXIT_SUCCESS);
        }
    }

    // Parent process
    int status;
    struct rusage child_rusage;
    struct timeval total_user_time, total_kernel_time;

    gettimeofday(&total_user_time, NULL);
    gettimeofday(&total_kernel_time, NULL);

    for (int i = 0; i < n; ++i) {
        if (wait4(-1, &status, 0, &child_rusage) == -1) {
            perror("wait4");
            exit(EXIT_FAILURE);
        }

        printf("Child %d (PID: %d) has terminated.\n", i+1, waitpid(-1, &status, 0));

        // Accumulate user and kernel time
        timeradd(&child_rusage.ru_utime, &total_user_time, &total_user_time);
        timeradd(&child_rusage.ru_stime, &total_kernel_time, &total_kernel_time);
    }

    printf("\nTotal Cumulative User Time: %ld.%06ld seconds\n", total_user_time.tv_sec, total_user_time.tv_usec);
    printf("Total Cumulative Kernel Time: %ld.%06ld seconds\n", total_kernel_time.tv_sec, total_kernel_time.tv_usec);

    return 0;
}
