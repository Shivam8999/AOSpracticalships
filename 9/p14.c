// Write a C program to Identify the type (Directory, character device, Block device, Regular file, FIFO or pipe, symbolic link or socket) of given file using stat() system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat fileStat;

    // Use the stat() system call to retrieve file properties
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    // Determine and print the file type based on the file mode
    if (S_ISREG(fileStat.st_mode)) {
        printf("File type: Regular file\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("File type: Directory\n");
    } else if (S_ISCHR(fileStat.st_mode)) {
        printf("File type: Character device\n");
    } else if (S_ISBLK(fileStat.st_mode)) {
        printf("File type: Block device\n");
    } else if (S_ISFIFO(fileStat.st_mode)) {
        printf("File type: FIFO or pipe\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("File type: Symbolic link\n");
    } else if (S_ISSOCK(fileStat.st_mode)) {
        printf("File type: Socket\n");
    } else {
        printf("File type: Unknown\n");
    }

    return 0;
}
