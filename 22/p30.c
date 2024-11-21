// Write a C program to implement the following unix/linux command (use fork, pipe
// and exec system call). Your program should block the signal Ctrl-C and Ctrl-\ signal
// during the execution. i. Ls –l | wc –l

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Block Ctrl-C and Ctrl-\ signals
    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT);
    sigaddset(&block_set, SIGQUIT);
    sigprocmask(SIG_BLOCK, &block_set, NULL);

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

        // Unblock signals in the child process
        sigprocmask(SIG_UNBLOCK, &block_set, NULL);

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Redirect the standard output to write to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);

        // exec failed if we reach here
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect the standard input to read from the pipe
        dup2(pipe_fd[0], STDIN_FILENO);

        // Close the read end of the pipe
        close(pipe_fd[0]);

        // Execute 'wc -l'
        execlp("wc", "wc", "-l", NULL);

        // exec failed if we reach here
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
