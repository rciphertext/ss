#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

int main()
{
int fd=open("input.txt",O_RDWR);
char ch[1];
for(int i=0;i<10;i++)
{

        ch[0]=getchar();
        write(fd,ch,sizeof(ch));
}

close(fd);

int fd1=open("input.txt",O_RDWR);
int x=lseek(fd,10,SEEK_CUR);

for(int i=0;i<10;i++)
{
        ch=getchar();
        write(fd,ch,sizeof(ch));
}

printf("\n%d",x);
return 0;
}
//problem: getchar is reading \n therefore reducing number of read operation

