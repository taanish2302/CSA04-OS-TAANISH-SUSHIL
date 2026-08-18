/*
Q15. Design a C program to organise the file using a two level
     directory structure.

     In a two level directory, every user has their own separate
     directory of files. We simulate this using a 2D array of file
     names, one row per user.
*/

#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10

char directory[MAX_USERS][MAX_FILES][50];   // directory[user][file]
int file_count[MAX_USERS] = {0};             // number of files each user has

void create_file(int user)
{
    if (file_count[user] >= MAX_FILES)
    {
        printf("This user's directory is full\n");
        return;
    }

    printf("Enter file name to create: ");
    scanf("%s", directory[user][file_count[user]]);
    file_count[user]++;
    printf("File created for user %d\n", user);
}

void delete_file(int user)
{
    char name[50];
    int i, j, found = 0;

    printf("Enter file name to delete: ");
    scanf("%s", name);

    for (i = 0; i < file_count[user]; i++)
    {
        if (strcmp(directory[user][i], name) == 0)
        {
            found = 1;
            for (j = i; j < file_count[user] - 1; j++)
                strcpy(directory[user][j], directory[user][j + 1]);
            file_count[user]--;
            break;
        }
    }

    if (found)
        printf("File deleted\n");
    else
        printf("File not found\n");
}

void display_files(int user)
{
    int i;
    printf("\nFiles belonging to user %d:\n", user);
    for (i = 0; i < file_count[user]; i++)
        printf("%d. %s\n", i + 1, directory[user][i]);
}

int main()
{
    int choice, user;

    do
    {
        printf("\n--- Two Level Directory ---\n");
        printf("1. Create file\n");
        printf("2. Delete file\n");
        printf("3. Display files of a user\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1 || choice == 2 || choice == 3)
        {
            printf("Enter user number (0 to %d): ", MAX_USERS - 1);
            scanf("%d", &user);
        }

        switch (choice)
        {
            case 1: create_file(user); break;
            case 2: delete_file(user); break;
            case 3: display_files(user); break;
            case 4: printf("Exiting\n"); break;
            default: printf("Invalid choice\n");
        }

    } while (choice != 4);

    return 0;
}
