// Implementation of ls -l using C
#include <sys/stat.h>
#include <types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>

void filePermissions(unsigned int); // Function to print permissions for the file
void fileHardlinks(int); // Function to print number of Hard Links
void fileUID(uid_t); // Function to print UID of the File Owner
void fileGID(gid_t); // Function to print Group ID of tbe File Owner
void fileSize(off_t); // Function to print Size of the File
void fileModTime(time_t); // Function to print Last Modified Time of the File
void fileName(char *); // Function to print Name of the File

int main(int argc, char **argv)
{
  struct stat sfile;
  struct dirent *myfile;
  DIR *dir;
  char buff[512];
  if (argc < 3) // Checking if we have sufficient arguments
  {
    printf("%s","ls: Not enough arguments.");
    return -1;
  }
  dir = opendir(argv[1]); 
  while((myfile = readdir(dir)) != NULL)
  {
    sprintf(buf, "%s/%s", argv[1], myfile->d_name); // Get full name of the file (Directory Name + "/" + File Name)
    stat(buf, &sfile);
    filePermissions(sfile.st_mode); // Permissions for the file
    printf(" ");
    fileHardlinks(sfile.st_nlink); // Number of Hard Links
    printf(" ");
    fileUID(sfile.st_uid); // UID of the File Owner
    printf(" ");
    fileGID(sfile.st_gid); // Group ID of tbe File Owner
    printf(" ");
    fileSize(sfile.st_size); // Size of the File
    printf(" ");
    fileModTime(sfile.st_mtime); // Last Modified Time of the File
    printf(" ");
    fileName(myfile->d_name); // Name of the File
    printf("\n");
  }
  return 0;
}

void filePermissions(unsigned int permissions); // Function to print permissions for the file
{
  if (S_ISDIR(permissions))        // Returns true if directory, false otherwise
    printf("d");
  else 
    printf("-");
  printf((permissions & S_IRUSR) ? "r" : "-");    // Print r if owner has read permision, otherwise -
  printf((permissions & S_IWUSR) ? "w" : "-");    // Print w if owner has write permission, otherwise -
  printf((permissions & S_IXUSR) ? "x" : "-");    // Print x if owner has execute permission, otherwise -
  printf((permissions & S_IRGRP) ? "r" : "-");
  printf((permissions & S_IWGRP) ? "w" : "-");
  printf((permissions & S_IXGRP) ? "x" : "-");
  printf((permissions & S_IROTH) ? "r" : "-");
  printf((permissions & S_IWOTH) ? "w" : "-");
  printf((permissions & S_IXOTH) ? "x" : "-");
  return;
}

void fileHardlinks(int n); // Function to print number of Hard Links
{
  printf("%d", n);
  return;
}

void fileUID(uid_t uid); // Function to print UID of the File Owner
{
  struct passwd user;         // Struct passwd to get username from UID
  user=*getpwuid(uid);       
  printf("%s", user.pw_name);
  return;
}

void fileGID(gid_t gid); // Function to print Group ID of tbe File Owner
{
  struct passwd group;         // Struct passwd to get group from UID
  group=*getpwuid(gid);       
  printf("%s", group.pw_name);
  return;
}

void fileSize(off_t size); // Function to print Size of the File
{
  printf("%ld", (long) size);       // Type cast off_t to long int and print
  return;
}

char* getMonth(int n) // Helper function to get abbreviated month name from month number
{
  switch(n)
  {
    case 1: return 'Jan';
            break;
    case 2: return 'Feb';
            break;
    case 3: return 'Mar';
            break;
    case 4: return 'Apr';
            break;
    case 5: return 'May';
            break;
    case 6: return 'Jun';
            break;
    case 7: return 'Jul';
            break;
    case 8: return 'Aug';
            break;
    case 9: return 'Sep';
            break;
    case 10: return 'Oct';
            break;
    case 11: return 'Nov';
            break;
    case 12: return 'Dec';
            break;
  }
}

void fileModTime(time_t t); // Function to print Last Modified Time of the File
{
  struct tm time;
  time=*localtime(&t);          //convert time_t format to tm format -- struct * tm = localtime(&time_t)
  printf("%s %d ", getMonth(time.tm_mon), time.tm_mday);
  if((time.tm_hour/10)==0)        //print leading '0' if less than 10
    printf("0");
  printf("%d:", time.tm_hour);
  if((time.tm_min/10)==0)
    printf("0");
  printf("%d ", time.tm_min);
  return;
}

void fileName(char *filename); // Function to print Name of the File
{
  printf("%s", filename);
  return;
}