#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    // Fork a new process
    pid_t pid = fork();
    if (pid > 0) {  // Parent process
        // Write to the file
        const char *parent_message = "Parent writes this.\n";
        write(fd, parent_message, 19);  // Write 19 characters
        wait(NULL);  // Wait for the child to finish
        close(fd);  // Close file descriptor in the parent process
    } else if (pid == 0) {  // Child process
        // Write to the file
        const char *child_message = "Child writes this.\n";
        write(fd, child_message, 18);  // Write 18 characters
        close(fd);  // Close the file descriptor in the child process
    } else {
        printf("Fork failed!");
        return 1;
    }

    return 0;
}