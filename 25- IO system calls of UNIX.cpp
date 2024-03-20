#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    // fcntl example
    int fd = open("example.txt", O_RDONLY);
    int flags = fcntl(fd, F_GETFL);
    printf("File Descriptor flags: %d\n", flags);
    close(fd);

    // seek example
    FILE *file = fopen("example.txt", "r");
    fseek(file, 10, SEEK_SET);
    char buffer[100];
    fread(buffer, sizeof(char), 10, file);
    printf("Read from position 10: %s\n", buffer);
    fclose(file);

    // stat example
    struct stat fileStat;
    stat("example.txt", &fileStat);
    printf("File Size: %ld bytes\n", fileStat.st_size);

    // opendir and readdir example
    DIR *dir = opendir(".");
    struct dirent *entry;
    printf("Files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}

