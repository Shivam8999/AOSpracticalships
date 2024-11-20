//Question - Take multiple files as Command Line Arguments and print their inode numbers and file types  
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat file_stat;

        if (stat(filename, &file_stat) == -1) {
            perror("stat");
            continue; // Skip to the next file
        }

        printf("File: %s\n", filename);
        printf("Inode Number: %lu\n", (unsigned long)file_stat.st_ino);
        printf("\n");
    }

    return 0;
}
