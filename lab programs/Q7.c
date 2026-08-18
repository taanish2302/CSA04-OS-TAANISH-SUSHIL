/*
Q7. Construct a C program to implement a non-preemptive SJF
    algorithm.

    This version also takes arrival time into account: at every
    point we choose, among the processes that have already arrived
    and are not finished, the one with the smallest burst time.
*/

#include <stdio.h>

int main()
{
    int n, i, time, completed, id;
    int at[20], bt[20], done[20];
    int wt[20], tat[20];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time of P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        done[i] = 0;   // 0 means not yet completed
    }

    time = 0;
    completed = 0;

    while (completed < n)
    {
        id = -1;
        int shortest = 9999;

        // find un-finished process that has arrived and has
        // the smallest burst time
        for (i = 0; i < n; i++)
        {
            if (!done[i] && at[i] <= time && bt[i] < shortest)
            {
                shortest = bt[i];
                id = i;
            }
        }

        if (id == -1)
        {
            // nothing has arrived yet, move time forward
            time++;
            continue;
        }

        // run this process fully (non-preemptive, so no interruption)
        wt[id] = time - at[id];
        time += bt[id];
        tat[id] = wt[id] + bt[id];

        done[id] = 1;
        completed++;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
