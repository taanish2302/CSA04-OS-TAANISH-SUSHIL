/*
Q9. Illustrate the concept of inter-process communication using
    shared memory with a C program.

    The parent process writes a message into a shared memory segment
    and the child process reads it from there.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main()
{
    int shmid;
    char *shared_mem;
    pid_t pid;

    // create a shared memory segment of 1024 bytes
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        printf("shmget failed\n");
        exit(1);
    }

    pid = fork();

    if (pid == 0)
    {
        // child process: read the message written by the parent
        sleep(1);   // give parent time to write first

        shared_mem = (char *) shmat(shmid, NULL, 0);
        printf("Child read from shared memory: %s\n", shared_mem);

        shmdt(shared_mem);   // detach from shared memory
    }
    else
    {
        // parent process: write a message into shared memory
        shared_mem = (char *) shmat(shmid, NULL, 0);

        printf("Enter message to share: ");
        fgets(shared_mem, 1024, stdin);

        printf("Parent wrote to shared memory\n");

        shmdt(shared_mem);
        wait(NULL);              // wait for child to finish

        shmctl(shmid, IPC_RMID, NULL);   // remove shared memory segment
    }

    return 0;
}
