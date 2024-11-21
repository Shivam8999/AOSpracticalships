// Write a program that illustrates how to execute two commands concurrently with a pipe.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid1, child_pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child process
    if ((child_pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid1 == 0) {
        // Child process 1

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Redirect the standard output to write to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Execute the first command (e.g., 'ls')
        execlp("ls", "ls", NULL);

        // exec failed if we reach here
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Fork the second child process
    if ((child_pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid2 == 0) {
        // Child process 2

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect the standard input to read from the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Execute the second command (e.g., 'wc -l')
        execlp("wc", "wc", "-l", NULL);

        // exec failed if we reach here
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process

    // Close both ends of the pipe as they are not needed in the parent
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to complete
    waitpid(child_pid1, NULL, 0);
    waitpid(child_pid2, NULL, 0);

    return 0;
}
