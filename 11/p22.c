// Write a C program to get and set the resource limits such as files, memory associated
// with a process

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void display_limits() {
    struct rlimit limits;

    // Get the current file size limit
    if (getrlimit(RLIMIT_FSIZE, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Current file size limit: %ld\n", (long)limits.rlim_cur);
}

void set_limit(long limit_value) {
    struct rlimit new_limit;

    // Get the current file size limit
    if (getrlimit(RLIMIT_FSIZE, &new_limit) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    // Set the new file size limit
    new_limit.rlim_cur = limit_value;
    if (setrlimit(RLIMIT_FSIZE, &new_limit) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    printf("New file size limit set: %ld\n", limit_value);
}

int main() {
    display_limits();

    long new_limit_value = 1024 * 1024 * 2; // 2 MB

    printf("Setting new file size limit to %ld bytes.\n", new_limit_value);
    set_limit(new_limit_value);

    display_limits();

    return 0;
}
