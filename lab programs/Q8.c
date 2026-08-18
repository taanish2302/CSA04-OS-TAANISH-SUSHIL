/*
Q8. Construct a C program to simulate Round Robin scheduling
    algorithm with C.
*/

#include <stdio.h>

int main()
{
    int n, i, tq, time = 0;
    int bt[20], rem_bt[20], wt[20], tat[20];
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time of each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];   // remaining burst time, used to track progress
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    // keep looping over all processes, giving each one "tq" units of
    // CPU time per turn, until all of them are finished
    int all_done;
    do
    {
        all_done = 1;

        for (i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                all_done = 0;   // still some process left to run

                if (rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    // this process finishes within this turn
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!all_done);

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
