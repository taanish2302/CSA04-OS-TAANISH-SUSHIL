/*
Q16. Develop a C program for implementing random access file for
     processing the employee details.

     Random access means we can jump directly to any employee's
     record using fseek(), instead of reading the file from the start.
*/

#include <stdio.h>
#include <string.h>

struct Employee
{
    int id;
    char name[50];
    float salary;
};

int main()
{
    FILE *fp;
    struct Employee emp;
    int choice, n, i, record_no;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL)
    {
        // file does not exist yet, create it
        fp = fopen("employee.dat", "wb+");
    }

    do
    {
        printf("\n--- Employee Random Access File ---\n");
        printf("1. Add employee records\n");
        printf("2. Read a particular record\n");
        printf("3. Update a particular record\n");
        printf("4. Display all records\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("How many employees to add? ");
            scanf("%d", &n);

            // move to the end of the file before adding new records
            fseek(fp, 0, SEEK_END);

            for (i = 0; i < n; i++)
            {
                printf("Enter id, name, salary: ");
                scanf("%d %s %f", &emp.id, emp.name, &emp.salary);
                fwrite(&emp, sizeof(emp), 1, fp);
            }
        }
        else if (choice == 2)
        {
            printf("Enter record number to read (starting from 0): ");
            scanf("%d", &record_no);

            // jump directly to that record's position in the file
            fseek(fp, record_no * sizeof(emp), SEEK_SET);

            if (fread(&emp, sizeof(emp), 1, fp) == 1)
                printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
            else
                printf("Record not found\n");
        }
        else if (choice == 3)
        {
            printf("Enter record number to update (starting from 0): ");
            scanf("%d", &record_no);

            printf("Enter new id, name, salary: ");
            scanf("%d %s %f", &emp.id, emp.name, &emp.salary);

            fseek(fp, record_no * sizeof(emp), SEEK_SET);
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Record updated\n");
        }
        else if (choice == 4)
        {
            fseek(fp, 0, SEEK_SET);   // go back to the beginning
            printf("\nID\tName\tSalary\n");
            while (fread(&emp, sizeof(emp), 1, fp) == 1)
                printf("%d\t%s\t%.2f\n", emp.id, emp.name, emp.salary);
        }

    } while (choice != 5);

    fclose(fp);
    return 0;
}
