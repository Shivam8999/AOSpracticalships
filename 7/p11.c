// Write a C Program that demonstrates redirection of standard output to a file
#include <stdio.h>

int main() {
    // Redirect standard output to a file
    FILE *file = freopen("output.txt", "w", stdout);

    if (file == NULL) {
        perror("freopen");
        return 1;
    }

    // Print to the redirected stdout
    printf("This output is redirected to a file.\n");

    // Close the file (optional)
    fclose(file);

    return 0;
}
