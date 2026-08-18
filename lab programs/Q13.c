/*
Q13. Construct a C program for implementation of the various memory
     allocation strategies.

     This program lets the user choose First Fit, Best Fit or Worst
     Fit and then allocates each process to a memory block accordingly.
*/

#include <stdio.h>

int main()
{
    int nblocks, nprocess, i, j, choice;
    int block[20], process[20];
    int allocation[20];   // allocation[i] = index of block given to process i

    printf("Enter number of memory blocks: ");
    scanf("%d", &nblocks);

    printf("Enter size of each block:\n");
    for (i = 0; i < nblocks; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &nprocess);

    printf("Enter size of each process:\n");
    for (i = 0; i < nprocess; i++)
        scanf("%d", &process[i]);

    printf("\nChoose allocation strategy:\n");
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n");
    scanf("%d", &choice);

    for (i = 0; i < nprocess; i++)
        allocation[i] = -1;   // -1 means not allocated

    for (i = 0; i < nprocess; i++)
    {
        int selected = -1;

        if (choice == 1)
        {
            // First Fit: pick the first block big enough
            for (j = 0; j < nblocks; j++)
            {
                if (block[j] >= process[i])
                {
                    selected = j;
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            // Best Fit: pick the smallest block that is still big enough
            for (j = 0; j < nblocks; j++)
            {
                if (block[j] >= process[i])
                {
                    if (selected == -1 || block[j] < block[selected])
                        selected = j;
                }
            }
        }
        else if (choice == 3)
        {
            // Worst Fit: pick the largest available block
            for (j = 0; j < nblocks; j++)
            {
                if (block[j] >= process[i])
                {
                    if (selected == -1 || block[j] > block[selected])
                        selected = j;
                }
            }
        }

        if (selected != -1)
        {
            allocation[i] = selected;
            block[selected] -= process[i];   // reduce remaining space in that block
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (i = 0; i < nprocess; i++)
    {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\tBlock %d\n", i + 1, process[i], allocation[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    return 0;
}
