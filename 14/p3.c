//Question- Write a C program to find file properties such as inode number, number of hard link, File permissions, File size, File access and modification time and so on of a given file using stat() system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_file_properties(const char *filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        return;
    }

    printf("File: %s\n", filename);
    printf("Inode Number: %lu\n", (unsigned long)file_stat.st_ino);
    printf("Number of Hard Links: %lu\n", (unsigned long)file_stat.st_nlink);
    printf("File Size: %ld bytes\n", (long)file_stat.st_size);
    printf("File Permissions: ");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    struct passwd *owner_info = getpwuid(file_stat.st_uid);
    struct group *group_info = getgrgid(file_stat.st_gid);

    if (owner_info != NULL)
        printf("Owner: %s\n", owner_info->pw_name);

    if (group_info != NULL)
        printf("Group: %s\n", group_info->gr_name);

    printf("Last Access Time: %s", ctime(&file_stat.st_atime));
    printf("Last Modification Time: %s", ctime(&file_stat.st_mtime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    print_file_properties(filename);

    return 0;
}
