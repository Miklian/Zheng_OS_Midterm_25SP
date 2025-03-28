#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid > 0) {  // Parent process
        sleep(1); // Parent waits for 1 second before printing
        printf("Goodbye!\n");
    } else if (pid == 0) {  // Child process
        printf("Hello!\n");
        exit(0); // Child exits immediately after printing
    } else {
        printf("Fork failed!");
        return 1;
    }

    return 0;
}