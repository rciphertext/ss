#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>


extern char **environ;
int main()
{
int i = 0;
while(environ[i]) 
{
  printf("%s\n", environ[i++]); // prints in form of "variable=value"
}
}
