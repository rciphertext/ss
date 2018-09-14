#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>i

int main()
{
	struct flock fp;

	fp.l_type=F_WRLCK;
	fp.l_whence=SEEK_SET;
	fp.l_start=0;
	fp.l_len=0;
	fp.l_pid=getpid();

	int f=open("input.txt",O_WRONLY | O_CREAT);
	
	if(f==-1)
	{
		printf("unable to open file for reading\n");
	}
	
	else
	{
		if(fcntl(f,F_SETLKW,&fp)==-1)
		{
			printf("UNABLE TO LOCK THE FILE");
			exit(1);
		}

		printf("LOCKED\n");
		printf("Enter the ticket number \n");

		char str;
		
		lseek(f,0,SEEK_SET);

		read(0,&str,strlen(str));
		printf("Ticket number is :%d",str);
		
		str++;

		write(f,&str,strlen(str));
	
		close(f);
		
		return 0;

	}	

}
