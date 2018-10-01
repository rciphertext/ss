#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int user_authentication(char * userid ,char * pass)
{
	struct detail u;
	static int count=0,set=0;
	int ofd = open("user_db.dat", O_RDONLY, 0766);

	if(ofd == -1){printf("cannot open user_db.dat file");}
	
	while((count=read(ofd, &u, sizeof(u)))!=0)
	{
		if((strcmp(userid,u.username)==0) && (strcmp(pass,u.password)==0))
		{		
		set=1;
		break;
		}
	}
	
	
	if(set==1)
	{
		return 2;
	}

	else
	{
		return 0;
	}
	
}
