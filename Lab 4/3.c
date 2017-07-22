// List all file names in a directory
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void printSize(char *filename)
{
    printf("%s\n", filename);       // Type cast off_t to long int and print
    return;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "\n%s", "Not Enough Arguments. Directory Name required.");
        return 1;
    }
    struct stat path_stat;
    stat(argv[1], &path_stat);
    if(!S_ISDIR(path_stat.st_mode)) // If a File
    {
        fprintf(stderr, "%s\n", "Not a Directory.");
        return 1;
    }
    struct dirent *myfile;
    DIR *dir = opendir(argv[1]);
    while((myfile = readdir(dir)) != NULL) // Else, a Directory
    {
        printSize(myfile->d_name);
        printf("\n");
    }
    return 0;
}