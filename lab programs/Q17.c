/*
Q17. Illustrate the deadlock avoidance concept by simulating
     Banker's algorithm with C.
*/

#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int alloc[20][20], max[20][20], need[20][20];
    int avail[20];
    int finish[20] = {0};
    int safe_seq[20];
    int count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter maximum need matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // need = max - allocation, this tells how much more each process
    // might still request
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // repeatedly look for a process whose need can be satisfied with
    // the currently available resources
    while (count < n)
    {
        int found = 0;

        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int can_allocate = 1;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate)
                {
                    // pretend process i runs to completion and
                    // gives back its resources
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];

                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            printf("\nSystem is NOT in a safe state (deadlock possible)\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\n");
    printf("Safe sequence: ");
    for (k = 0; k < n; k++)
        printf("P%d ", safe_seq[k]);
    printf("\n");

    return 0;
}
