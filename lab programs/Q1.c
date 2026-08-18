/*
Q1. Create a new process by invoking the appropriate system call.
    Get the process identifier of the currently running process and
    its respective parent using system calls and display the same.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    // fork() creates a new process (child) which is a copy of the parent
    pid = fork();

    if (pid < 0)
    {
        // fork failed
        printf("Fork failed\n");
    }
    else if (pid == 0)
    {
        // this block runs in the child process
        // fork() returns 0 to the child
        printf("Child process\n");
        printf("Process id of child   : %d\n", getpid());
        printf("Parent id of child    : %d\n", getppid());
    }
    else
    {
        // this block runs in the parent process
        // fork() returns child's pid to the parent
        printf("Parent process\n");
        printf("Process id of parent  : %d\n", getpid());
        printf("Parent id of parent   : %d\n", getppid());
    }

    return 0;
}
