//Display all the files from current directory which are created in particular month	 

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// Function to check if a file was created in a specific month
int isCreatedInMonth(const char *filename, int targetMonth) {
    struct stat fileStat;
    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return 0; // Error, assume not created in the target month
    }

    struct tm *creationTime = localtime(&fileStat.st_ctime);
    return creationTime->tm_mon + 1 == targetMonth; // +1 because months are 0-based
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target_month>\n", argv[0]);
        return 1;
    }

    int targetMonth = atoi(argv[1]);
    if (targetMonth < 1 || targetMonth > 12) {
        printf("Invalid month. Please enter a month between 1 and 12.\n");
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
    printf("Files created in month %d:\n", targetMonth);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && isCreatedInMonth(entry->d_name, targetMonth)) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}
