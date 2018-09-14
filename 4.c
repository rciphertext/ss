#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
int fd=open("input.txt",O_EXCL|O_CREAT);
int fd2=open("input.txt",O_EXCL);
printf("%d %d",fd,fd2);
return 0;
}
