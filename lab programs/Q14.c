/*
Q14. Construct a C program to organise the file using a single
     level directory.

     A single level directory means all files sit in one common
     directory - there are no sub folders. We simulate this using
     a simple array of file names.
*/

#include <stdio.h>
#include <string.h>

#define MAX_FILES 20

char directory[MAX_FILES][50];   // stores file names
int count = 0;                   // number of files currently in directory

void create_file()
{
    if (count >= MAX_FILES)
    {
        printf("Directory is full\n");
        return;
    }

    printf("Enter file name to create: ");
    scanf("%s", directory[count]);
    count++;
    printf("File created\n");
}

void delete_file()
{
    char name[50];
    int i, j, found = 0;

    printf("Enter file name to delete: ");
    scanf("%s", name);

    for (i = 0; i < count; i++)
    {
        if (strcmp(directory[i], name) == 0)
        {
            found = 1;
            // shift all files after this one, one position back
            for (j = i; j < count - 1; j++)
                strcpy(directory[j], directory[j + 1]);
            count--;
            break;
        }
    }

    if (found)
        printf("File deleted\n");
    else
        printf("File not found\n");
}

void search_file()
{
    char name[50];
    int i, found = 0;

    printf("Enter file name to search: ");
    scanf("%s", name);

    for (i = 0; i < count; i++)
    {
        if (strcmp(directory[i], name) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
        printf("File found\n");
    else
        printf("File not found\n");
}

void display_files()
{
    int i;
    printf("\nFiles in directory:\n");
    for (i = 0; i < count; i++)
        printf("%d. %s\n", i + 1, directory[i]);
}

int main()
{
    int choice;

    do
    {
        printf("\n--- Single Level Directory ---\n");
        printf("1. Create file\n");
        printf("2. Delete file\n");
        printf("3. Search file\n");
        printf("4. Display all files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: search_file(); break;
            case 4: display_files(); break;
            case 5: printf("Exiting\n"); break;
            default: printf("Invalid choice\n");
        }

    } while (choice != 5);

    return 0;
}
