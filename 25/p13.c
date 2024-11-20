//Write a C program that redirects standard output to a file output.txt. (use of dup and open system call)
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Save the current file descriptor for standard output (usually 1, stdout)
    int original_stdout = dup(STDOUT_FILENO);

    // Open the "output.txt" file for writing, creating it if it doesn't exist, and truncating it
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Use the dup2() system call to redirect standard output to the file descriptor of "output.txt"
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }

    // Now, anything printed to stdout will be redirected to "output.txt"

    // Print to the redirected stdout
    printf("This output is redirected to a file.\n");

    // Close the file descriptor and restore the original stdout
    close(fd);
    dup2(original_stdout, STDOUT_FILENO);

    // Continue to print to the original stdout (console)
    printf("This output goes to the console.\n");

    return 0;
}
