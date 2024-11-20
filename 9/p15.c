// Generate parent process to write unnamed pipe and will read from it
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    pid_t child_pid;

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        // Child process (reader)

        close(pipe_fd[1]); // Close the write end of the pipe

        char buffer[100];
        int bytes_read;

        // Read from the pipe
        bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));

        if (bytes_read == -1) {
            perror("read");
            exit(1);
        }

        printf("Child Process (Reader) received: %.*s\n", bytes_read, buffer);
        close(pipe_fd[0]); // Close the read end of the pipe in the child
    } else {
        // Parent process (writer)

        close(pipe_fd[0]); // Close the read end of the pipe

        // Write to the pipe
        const char *message = "Hello, Child!";
        if (write(pipe_fd[1], message, strlen(message)) == -1) {
            perror("write");
            exit(1);
        }

        close(pipe_fd[1]); // Close the write end of the pipe in the parent
    }

    return 0;
}
