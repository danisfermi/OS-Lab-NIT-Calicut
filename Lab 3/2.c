// Implemention of cp command in Linux using open(), read(), write() system calls
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
  char buffer[1024];
  int files[2];
  size_t count;
  if (argc<3) // Checking if we have sufficient arguments
    return -1;
  files[0] = open(argv[1], O_RDONLY);
  if (files[0] == -1) // Checking if the file opened
    return -1;
  files[1] = open(argv[2], O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR);
  if (files[1] == -1) // Checking if 2nd file opened
  {
    close(files[0]);
    return -1;
  }
  while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
    write(files[1], buffer, count);

  return 0;

}