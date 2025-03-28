#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid > 0) {  // Parent process
        printf("I'm the parent!! Did the child process print?\n");
        wait(NULL);
    } else if (pid == 0) {  // Child process
        close(STDOUT_FILENO);
        printf("Hello, I'm the child process printing!!!\n");
        exit(0);
    } else {
        printf("Fork failed!");
        return 1;
    }

    return 0;
}