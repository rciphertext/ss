#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>


int main()
{

	struct flock fp;

	fp.l_type=F_WRLCK;
	fp.l_whence=SEEK_SET;
	
	int rec=0;
	printf("Enter the record number(<3) you want to read :");
	scanf("%d",&rec);

	fp.l_start=rec+1;
	fp.l_len=1;
	fp.l_pid=getpid();

	printf("press enter \n");
	getchar();

	int f=open("record.txt",O_WRONLY);
	
	if(f==-1)
	{
		printf("unable to open file\n");
	}

	else
	{
		if(fcntl(f,F_SETLKW,&fp)==-1)
		{
			printf("fail to lock the file");
			exit(1);
		}

		printf("locked\n");
		
		char str[1];
		printf("Enter new record value \n:");
		
		lseek(f,rec+1,SEEK_SET);
		
		str[0]=getchar();
		write(f,str,strlen(str));
		printf("press enter to release the unlock\n");

		getchar();

		fp.l_type=F_UNLCK;

		if(fcntl(f,F_SETLK,&fp))
		{
			printf("error in releasing lock");
			exit(1);

		}


		printf("unlocked\n");
		close(f);
	}

return 0;

}
