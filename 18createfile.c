#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int f=open("record.txt",O_RDWR);

	printf("Enter the records :\n ");
	
	char str[1];	
	lseek(f,0,SEEK_SET);

	for(int i=0;i<3;i++)
	{
	
		while((str[0]=getchar())!='\n')
		{
		write(f,str,strlen(str));
		}

		str[0]='\n';
		write(f,str,strlen(str));
	}	
	return 0;



}
