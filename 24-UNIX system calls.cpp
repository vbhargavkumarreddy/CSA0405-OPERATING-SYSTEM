#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define FILENAME "example_file.txt"
void createFile() {
    int fd = open(FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    printf("File '%s' created successfully.\n", FILENAME);

    close(fd);
}
void writeFile() {
    int fd = open(FILENAME, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    const char *content = "Hello, this is a sample text.\n";
    write(fd, content, strlen(content));

    printf("Content written to the file.\n");

    close(fd);
}

void readFile() {
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    printf("\n");
    close(fd);
}
void deleteFile() {
    if (unlink(FILENAME) == -1) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }
    printf("File '%s' deleted successfully.\n", FILENAME);
}
int main() {
    createFile();
    writeFile();
    printf("\nFile Content:\n");
    readFile();
    deleteFile();
    return 0;
}
