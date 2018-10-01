#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "admin_struct.c"

int main(){
	struct adminid user;
	int count;
	int ofd = open("admin_db.dat", O_RDONLY, 0766);
	
	if(ofd == -1){printf("cannot open file");}
	do{
		printf("read %d bytes:\n",count = read(ofd, &user, sizeof(user)));
		if(count !=0){
		printf("Username: %s\nPassword: %s\n", user.username, user.password);		
		}
			
	}while(count != 0);	


return 0;
}
