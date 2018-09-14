#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	struct flock fp;

	fp.l_type=F_WRLCK;
	fp.l_whence=SEEK_SET;
	fp.l_start=0;
	fp.l_len=0;
	fp.l_pid=getpid();

	int f=open("input.txt",O_RDWR | O_CREAT);
	
	if(f==-1)
	{
		printf("unable to open file for writing\n");
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

		int str[1],sum=0;
		read(f,str,sizeof(str));
		printf("Ticket Number is :%d",str[0]);
		
		str[0]=str[0]+1;
		write(f,str,sizeof(str));
	

		close(f);
		exit(0);
		return 0;

	}	

}
