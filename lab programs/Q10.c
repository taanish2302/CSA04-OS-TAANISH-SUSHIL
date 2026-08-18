/*
Q10. Illustrate the concept of inter-process communication using
     message queue with a C program.

     The parent process sends a message through a message queue and
     the child process receives and displays it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

// structure of the message that will travel through the queue
struct msg_buffer
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    int msgid;
    struct msg_buffer message;
    pid_t pid;

    // create a message queue
    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgid < 0)
    {
        printf("msgget failed\n");
        exit(1);
    }

    pid = fork();

    if (pid == 0)
    {
        // child process: receive the message
        sleep(1);   // give parent time to send first

        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("Child received message: %s\n", message.msg_text);
    }
    else
    {
        // parent process: send a message
        message.msg_type = 1;
        printf("Enter message to send: ");
        fgets(message.msg_text, sizeof(message.msg_text), stdin);

        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("Parent sent the message\n");

        wait(NULL);   // wait for child to finish

        msgctl(msgid, IPC_RMID, NULL);   // remove the message queue
    }

    return 0;
}
