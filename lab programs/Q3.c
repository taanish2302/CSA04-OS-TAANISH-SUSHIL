/*
Q3. Design a CPU scheduling program with C using First Come First
    Served (FCFS) technique.
    Assumptions: all processes arrive at time 0, no process waits on I/O.
*/

#include <stdio.h>

int main()
{
    int n, i;
    int bt[20], wt[20], tat[20];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time of each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // in FCFS, waiting time of first process is always 0
    wt[0] = 0;

    // waiting time of every other process = sum of burst times of all
    // processes before it (since they arrive in the order they came)
    for (i = 1; i < n; i++)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // turnaround time = waiting time + burst time
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = wt[i] + bt[i];
        total_wt += wt[i];
        total_tat += tat[i];

        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
