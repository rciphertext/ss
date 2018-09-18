#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{	
	char str[80];
	//int fp[2];
	int fp1=open(stdin,O_RDONLY);
	int fp2=open(stdout,O_WRONLY);
	while(1)
	{
		read(fp1,str,sizeof(str));
		write(fp2,str,sizeof(str));	
	}

	return 0;
}

