/* Implementation of fsize to print the size of a given file (in linux, a directory is also
a kind of file). If the file is a directory, then make a directory walk to to apply 'fsize' on all
files in it. The output in this case should be the name(s) of files in the directory and its size. */
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void printSize(char *filename, off_t size)
{
    printf("%s: %ld", filename, (long) size);       // Type cast off_t to long int and print
    return;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "\n%s", "Not Enough Arguments. File/Directory Name required.");
        return 1;
    }
    struct stat path_stat;
    stat(argv[1], &path_stat);
    if(S_ISREG(path_stat.st_mode)) // If a File
    {
        printSize(argv[1], path_stat.st_size);
    }
    char buff[512];
    struct dirent *myfile;
    DIR *dir = opendir(argv[1]);
    while((myfile = readdir(dir)) != NULL) // Else, a Directory
    {
        sprintf(buff, "%s/%s", argv[1], myfile->d_name); // Get full name of the file (Directory Name + "/" + File Name)
        stat(buff, &path_stat);
        printSize(myfile->d_name, path_stat.st_size);
        printf("\n");
    }
    return 0;
}