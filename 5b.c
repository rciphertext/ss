#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
int fd=open("input.txt",O_RDONLY);
int fd2=open("input1.txt",O_RDONLY);
int fd3=open("input2.txt",O_RDONLY);
printf("%d %d %d",fd,fd2,fd3);	
	while(1);                                               

return 0;
}

