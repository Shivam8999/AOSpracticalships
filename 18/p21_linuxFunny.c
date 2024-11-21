// Write a C program to create an unnamed pipe. The child process will write following
// three messages to pipe and parent process display it.
// Message1 = “Hello World”
// Message2 = “Hello SPPU”
// Message3 = “Linux is Funny”

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MESSAGE1 "Hello World"
#define MESSAGE2 "Hello SPPU"
#define MESSAGE3 "Linux is Funny"

int main() {
    int pipe_fd[2];
    pid_t child_pid;
    char buffer[1024];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Write messages to the pipe
        write(pipe_fd[1], MESSAGE1, strlen(MESSAGE1) + 1);
        write(pipe_fd[1], MESSAGE2, strlen(MESSAGE2) + 1);
        write(pipe_fd[1], MESSAGE3, strlen(MESSAGE3) + 1);

        // Close the write end of the pipe
        close(pipe_fd[1]);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Read and display messages from the pipe
        while (read(pipe_fd[0], buffer, sizeof(buffer)) > 0) {
            printf("Parent process received: %s\n", buffer);
        }

        // Close the read end of the pipe
        close(pipe_fd[0]);

        wait(NULL); // Wait for the child process to complete

        exit(EXIT_SUCCESS);
    }

    return 0;
}
