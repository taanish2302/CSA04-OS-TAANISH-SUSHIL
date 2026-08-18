/*
Q12. Design a C program to simulate the concept of Dining
     Philosophers problem.

     Each philosopher needs both the left and the right fork to eat.
     Forks are represented as semaphores. To avoid deadlock, every
     philosopher picks up the lower-numbered fork first.

     Compile with: gcc Q12.c -o Q12 -lpthread
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // number of philosophers

sem_t fork_sem[N];   // one semaphore (fork) between each pair of philosophers

void *philosopher(void *num)
{
    int id = *(int *) num;
    int left = id;
    int right = (id + 1) % N;

    // always pick up the lower numbered fork first, this ordering
    // is what prevents circular waiting (deadlock)
    int first = (left < right) ? left : right;
    int second = (left < right) ? right : left;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    sem_wait(&fork_sem[first]);
    printf("Philosopher %d picked up fork %d\n", id, first);

    sem_wait(&fork_sem[second]);
    printf("Philosopher %d picked up fork %d\n", id, second);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&fork_sem[second]);
    sem_post(&fork_sem[first]);
    printf("Philosopher %d put down forks and is done\n", id);

    return NULL;
}

int main()
{
    pthread_t phil[N];
    int id[N];
    int i;

    // initialize each fork as available (value 1)
    for (i = 0; i < N; i++)
        sem_init(&fork_sem[i], 0, 1);

    for (i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &id[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(phil[i], NULL);

    for (i = 0; i < N; i++)
        sem_destroy(&fork_sem[i]);

    return 0;
}
