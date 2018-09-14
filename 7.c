#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
int fd1;
int fd2;
fd1=open("input.txt",O_RDONLY);
fd2=open("output.txt",O_WRONLY);

char str[1];

while(read(fd1,str,sizeof(str))!=0)
{
printf("%s\n",str);
write(fd2,str,sizeof(str));
}
return 0;
}
