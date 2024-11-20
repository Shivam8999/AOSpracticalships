//Question-  Read the current directory and display the name of the files, no of files in current directory	pract
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int fileCount = 0; // Variable to count files

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Iterate through directory entries
    printf("Files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file (not a directory or special file)
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
            fileCount++;
        }
    }

    // Close the directory
    closedir(dir);

    // Display the total number of files
    printf("Total number of files: %d\n", fileCount);

    return 0;
}
