#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>


int main()
{
	
printf("Enter the file name/path \n ");
char *fd=getchar();

struct stat * buf=(struct stat *)malloc(sizeof(struct stat));

stat(fd, buf);
char *type= buf->st_mode;

printf("%s",*type);
return 0;
}
