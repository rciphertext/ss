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
FILE *fp;
fp=fopen("input.txt","r");
fd1=open("input.txt",O_RDONLY);
fd2=open(stdin,O_WRONLY);
char str[1];
char ch;
while(read(fd1,str,sizeof(str))!=0)
{
	if(str[0]=='\n')
	{
		ch=getchar();
		putchar(ch);
	}
	printf("%s",str);
}
return 0;
}

