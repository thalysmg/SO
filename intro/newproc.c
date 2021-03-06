#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
    char *argv[3];
    pid_t pid, donep;
    pid = 0;
    pid = fork();
    if (pid == 0) {
    	printf("Upon successful completion, fork() returns a value of 0 to the child process\n");
	    printf("child dying\n");
	    exit(0);
    } else {
        printf("Upon successful completion, fork() returns returns the process ID of the child process to the parent process\n");
	    donep = wait(0);
	    printf("child %d has gone\n", donep);
        return 0;
    }
}

