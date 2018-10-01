#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "admin_struct.c"


int admin_authentication(char * userid ,char * pass)
{
	struct adminid a;
	static int count=0,set=0;
	int ofd = open("admin_db.dat", O_RDONLY, 0766);

	if(ofd == -1){printf("cannot open file");}
	
	while((count=read(ofd, &a, sizeof(a)))!=0)
	{
		if((strcmp(userid,a.username)==0) && (strcmp(pass,a.password)==0))
		{		
		set=1;
		break;
		}
	}
	
	
	if(set==1)
	{
		return 1;
	}

	else
	{
		return 0;
	}
	
}
