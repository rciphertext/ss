#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	struct flock fp;

	fp.l_type=F_RDLCK;
	fp.l_whence=SEEK_SET;
	fp.l_start=0;
	fp.l_len=20;
	fp.l_pid=getpid();

	printf("press enter \n");
	getchar();

	int f=open("input.txt",O_RDWR);
	
	if(f==-1)
	{
		printf("unable to open file\n");
	}
	
	else
	{
		if(fcntl(f,F_SETLKW,&fp)==-1)
		{
			printf("fcntl cause error");
			exit(1);
		}

		printf("locked\n");
		printf("press enter to release the lock\n ");

		getchar();
		
		fp.l_type=F_UNLCK;

		if(fcntl(f,F_SETLK,&fp))
		{
			printf("error in releasing liock");
			exit(1);

		}


		printf("unlocked\n");
		close(f);
		return 0;

	}	

}
