/*
Q2. Identify the system calls to copy the content of one file to
    another and illustrate the same using a C program.

    System calls used: open(), read(), write(), close()
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char source[100], destination[100];
    char buffer[1024];
    int src_fd, dest_fd, n;

    printf("Enter source file name: ");
    scanf("%s", source);

    printf("Enter destination file name: ");
    scanf("%s", destination);

    // open source file in read only mode
    src_fd = open(source, O_RDONLY);
    if (src_fd == -1)
    {
        printf("Cannot open source file\n");
        return 1;
    }

    // open (or create) destination file in write only mode
    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1)
    {
        printf("Cannot open destination file\n");
        close(src_fd);
        return 1;
    }

    // read from source and write into destination, 1024 bytes at a time
    while ((n = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        write(dest_fd, buffer, n);
    }

    printf("File copied successfully\n");

    close(src_fd);
    close(dest_fd);

    return 0;
}
