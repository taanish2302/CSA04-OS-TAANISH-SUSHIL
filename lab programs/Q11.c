/*
Q11. Illustrate the concept of multithreading using a C program.

     Compile with: gcc Q11.c -o Q11 -lpthread
*/

#include <stdio.h>
#include <pthread.h>

// function that each thread will run
void *print_message(void *arg)
{
    char *message = (char *) arg;
    printf("Thread says: %s\n", message);
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    char *msg1 = "Hello from thread 1";
    char *msg2 = "Hello from thread 2";

    // create two threads, each running print_message()
    pthread_create(&t1, NULL, print_message, (void *) msg1);
    pthread_create(&t2, NULL, print_message, (void *) msg2);

    // wait for both threads to finish before main() exits
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Both threads have finished\n");

    return 0;
}
