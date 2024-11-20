// Display all the files from current directory whose size is greater that n Bytes Where n is accept from user.
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size_in_bytes>\n", argv[0]);
        return 1;
    }

    long long n = atoll(argv[1]); // Convert the size argument to a long long integer

    if (n < 0) {
        printf("Invalid size. Please enter a non-negative number.\n");
        return 1;
    }

    DIR *dir;
    struct dirent *entry;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Iterate through directory entries
    printf("Files larger than %lld bytes:\n", n);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            struct stat fileStat;
            if (stat(entry->d_name, &fileStat) == -1) {
                perror("stat");
                continue; // Skip this file and move to the next
            }

            if (fileStat.st_size > n) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
