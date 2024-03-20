#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Check if a directory path is provided as a command-line argument
    if (argc != 2) {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    // Open the specified directory
    DIR *dir = opendir(argv[1]);

    // Check if the directory is opened successfully
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Read and print the contents of the directory
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

