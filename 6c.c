#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
char * path="ipc";
mkfifo(path,0666);
char str[100];
int fd1;
while(1)
{
fd1=open(path,O_RDONLY);

read(fd1,str,100);
printf("%s",str);
close(fd1);
}


return 0;
}
