#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char** argv)
{
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    if (argc != 4)
    {
        fprintf(stderr, "\n%s", "Not Enough Arguments. File Name, Start Position and Stop Position required.");
        exit(1);
    }
    int file = open(argv[1], O_RDONLY);
    if (file < 0)
    {
        fprintf(stderr, "\n%s", "Unable to open file.");
        exit(1);
    }
    if (lseek(file, start, SEEK_SET) < 0)
    {
        fprintf(stderr, "\n%s", "Error performing lseek().");
        exit(1);
    }
    char* buffer = (char*)malloc(end+1);
    if (buffer == 0)
    {
        fprintf(stderr, "\n%s", "Malloc Failure.");
        exit(1);
    }
    size_t nbytes = read(file, buffer, sizeof(buffer));
    if(!nbytes)
    {
        printf("\nRead: %s", buffer);
    }
    return 0;
}