#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } 
    else if (pid == 0) {
        execlp("/bin/ls","ls",NULL);
    } 
    else {
        // This block is executed by the Parent Process
	wait(NULL);
        printf("Child Complete");
    }

    return 0;
}
