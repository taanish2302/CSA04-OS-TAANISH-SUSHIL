/*
Q6. Construct a C program to implement preemptive priority
    scheduling algorithm.

    Smaller priority number = higher priority.
    We simulate the CPU time unit by time unit and, at every unit,
    pick the process with the highest priority among those that have
    arrived and are not yet finished.
*/

#include <stdio.h>

int main()
{
    int n, i, time, completed, id;
    int at[20], bt[20], pr[20], rem_bt[20];
    int wt[20], tat[20];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time, burst time, priority of P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
        rem_bt[i] = bt[i];
    }

    time = 0;
    completed = 0;

    // keep running until all processes are completed
    while (completed < n)
    {
        id = -1;
        int best_priority = 9999;

        // choose the process with highest priority (smallest number)
        // among processes that have arrived and still have work left
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0 && pr[i] < best_priority)
            {
                best_priority = pr[i];
                id = i;
            }
        }

        if (id == -1)
        {
            // no process has arrived yet, CPU is idle
            time++;
            continue;
        }

        // run the chosen process for one unit of time
        rem_bt[id]--;
        time++;

        if (rem_bt[id] == 0)
        {
            completed++;
            tat[id] = time - at[id];          // turnaround time
            wt[id] = tat[id] - bt[id];         // waiting time
        }
    }

    printf("\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
