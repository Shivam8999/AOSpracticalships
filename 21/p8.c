// Write a C program which receives file names as command line arguments and display those filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …)
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Structure to store file information (name and size)
struct FileInfo {
    char *name;
    off_t size;
};

// Comparison function for sorting FileInfo structures by size in ascending order
int compareFileInfo(const void *a, const void *b) {
    return ((struct FileInfo *)a)->size - ((struct FileInfo *)b)->size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    // Create an array of FileInfo structures
    int numFiles = argc - 1;
    struct FileInfo *fileInfoArray = (struct FileInfo *)malloc(numFiles * sizeof(struct FileInfo));

    if (fileInfoArray == NULL) {
        perror("malloc");
        return 1;
    }

    // Retrieve file sizes and store them in the array
    for (int i = 1; i <= numFiles; i++) {
        struct stat fileStat;
        if (stat(argv[i], &fileStat) == -1) {
            perror("stat");
            return 1;
        }

        fileInfoArray[i - 1].name = argv[i];
        fileInfoArray[i - 1].size = fileStat.st_size;
    }

    // Sort the FileInfo array based on file sizes
    qsort(fileInfoArray, numFiles, sizeof(struct FileInfo), compareFileInfo);

    // Display the sorted file names
    printf("File names in ascending order of sizes:\n");
    for (int i = 0; i < numFiles; i++) {
        printf("%s\n", fileInfoArray[i].name);
    }

    // Free dynamically allocated memory
    free(fileInfoArray);

    return 0;
}
