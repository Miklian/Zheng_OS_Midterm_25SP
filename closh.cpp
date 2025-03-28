#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main() {
    string program;     // User: program name to run
    int execNum;   // User: num of copies to run
    char execType;      // User: [s]equential or [p]arallel

    while (true) {
        //Prompts
        cout << "closh> ";
        getline(cin, program);

        cout << "count> ";
        cin >> execNum;
        cin.ignore(); // Discarding /n

        cout << "[p]arallel or [s]equential> ";
        cin >> execType;
        cin.ignore();
        
        // execNum Validation
        if (execNum < 1 || execNum > 9) {
            cout << "Please specify a number of processes between 1 and 9." << endl;
            continue;
        }

        // Child process looping
        pid_t pid;
        for (int i = 0; i < execNum; ++i) {
            pid = fork();
            
            if (pid == -1) {
                // Error in forking
                perror("Fork failed");
                exit(1);
            } else if (pid == 0) {
                // Child process
                char* args[] = { (char*)program.c_str(), NULL };
                execvp(args[0], args);  // Execution

                // If execvp fails:
                perror("Execvp failed");
                exit(1);
            }

            // Sequential execution: Wait for each child to finish 
            if (execType == 's') { 
                // Parent Process
                waitpid(pid, NULL, 0);
            }
        }

        // Concurrent execution: parent doesn't wait for the child
        if (execType == 'p') {
            for (int i = 0; i < execNum; ++i) {
                waitpid(-1, NULL, 0);  // Wait for any child process to finish
            }
        }
    }

    return 0;
}