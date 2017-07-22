// Program to du (Disk Usage) command using fstat system call
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h> // For directory ops
#include <unistd.h> // For chdir
#include <string.h> // For strcmp, strcat

off_t du(char* dirname, char* path) // If direcoory, to recursively find the constituent file sizes
{
  off_t size = 0; // Size of Current Directory
  struct stat dentry; // To store file details
  DIR *dir = opendir(dirname);
  struct dirent *direntry; // To store directory details
  int fd = open(dirname, O_RDONLY);
  if (fstat(fd, &dentry) < 0) // Error fstating
  {
    fprintf(stderr, "\n%s", "Error Fstating File.");
    return 1;
  }
  size = size + 512*dentry.st_blocks; // Add Directory Size
  if (chdir(dirname) < 0) // Error entering Directory, probable access denial 
  {
    fprintf(stderr, "\n%s", "Error Accessing Directory.");
    return 1;
  }
  while((direntry=readdir(dir))!=NULL)          // Loop to iterate through the directory
  { 
    fd=open(direntry->d_name, O_RDONLY);
    if(fstat(fd, &dentry)==-1)
    {
      fprintf(stderr, "\n%s", "Error Fstating File.");
      return 1;
    }
    
    if(!S_ISDIR(dentry.st_mode))
      size += dentry.st_blocks*512;
    else if((strcmp(direntry->d_name, "..")==0)||(strcmp(direntry->d_name, ".")==0)) // Skip check if . or ..
      continue;
    else // If it is a directory in a directory
    { 
      
      char temp[1000];
      strcpy(temp, path);     
      size+=du(direntry->d_name, strcat(strcat(temp, "/"), direntry->d_name));                    
    }
    close(fd); 
  }
  printf("%ld %s", long(size/1024), dirname);
  printf("\t%s\n",path);
  if(chdir("..")==-1)
  {
    fprintf(stderr, "\nError Returning to Parent Directory");
    return 1;
  }
  closedir(dir);                //close the directory stream to clear memory.
  return size;
}

int main(int argc, char **argv)
{
  struct stat file;
  off_t size;
  if (argc == 1)
  {
    char temp[4] = ".";
    size = du(temp, temp); // Use currect directory if no arguments given by the user
    return 0;
  }
  if (argc != 2)
  {
    printf("%s\n", "Invalid Options to Command du. Format is du <directory>.");
    return 1;
  }
  if (stat(argv[1], &file) < 0)
  {
    fprintf(stderr, "\nError Opening File.");
    return 1;
  }
  if(!S_ISDIR(file.st_mode)) // If a file, orint the size of the file
  {
    printf("%ld %s", long((512*file.st_blocks)/1024), argv[1]);
    printf("\t%s\n", argv[1]);
  }
  else // If a directory, recursively find the constituent file sizes
    size = du(argv[1], argv[1]);
  return 0;
}