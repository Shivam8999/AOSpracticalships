// Write a C program that a string as an argument and return all the files that begins with that name in the current directory. For example > ./a.out foo will return all file names that begins with foo	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <prefix>\n", argv[0]);
        return 1;
    }

    const char *prefix = argv[1];
    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Iterate through directory entries
    printf("Files beginning with '%s' in the current directory:\n", prefix);
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file and starts with the specified prefix
        if (entry->d_type == DT_REG && strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
