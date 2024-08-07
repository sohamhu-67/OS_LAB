#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // For fork(), getpid(), getppid(), and exit()
#include <sys/wait.h> // For wait()

int main() {
    pid_t pid1, pid2;

    // Get and print the process ID of the current process
    pid1 = getpid();
    printf("Initial Process ID: %d\n", pid1);

    // Call fork to create a new process
    pid2 = fork();

    // Check if fork failed
    if (pid2 == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    // If fork was successful, pid2 will be 0 in the child process
    if (pid2 == 0) {
        // This is the child process
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID (in child): %d\n", getppid());
        exit(EXIT_SUCCESS); // Exit child process
    } else {
        // This is the parent process
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID (in parent): %d\n", pid2);
        // Wait for child process to complete
        wait(NULL);
        exit(EXIT_SUCCESS);  // Exit parent process
    }
}

