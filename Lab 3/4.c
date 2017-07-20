// Program to print Version Number and hardware details like sysname, release, version and processor.
#include <stdio.h>
#include <sys/utsname.h>
int main()
{
  struct utsname unameData;
  if(uname(&unameData)==0)
  {
      printf("\nSys Name: %s", unameData.sysname);
      printf("\nRelease: %s", unameData.release);
      printf("\nVersion: %s", unameData.version);
      printf("\nProcessor: %s", unameData.processor);
  }
  else
  {
    fprintf(stderr, "\nSystem Call to uname() failed.")
  }
  return 0;
}