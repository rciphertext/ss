#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
int fd1=open("file2.txt",O_CREAT|O_RDONLY);
//:int fd2=open("file1.txt",)
int x= symlink("file2.txt","file1.txt");
return 0;
}
