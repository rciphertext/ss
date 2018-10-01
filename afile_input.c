#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "admin_struct.c"
int main(){
	struct adminid user1, user2;
	strcpy(user1.username,  "ravi");
	strcpy(user1.password, "singh");
	strcpy(user2.username,  "ayush");
	strcpy(user2.password, "singh");
	int ofd = open("admin_db.dat", O_WRONLY | O_APPEND | O_CREAT, 0766);
	
	if(ofd == -1){printf("cannot open file");}
	else{
		printf("written %ld bytes:",write(ofd, &user1, sizeof(user1)));
		printf("written %ld bytes:",write(ofd, &user2, sizeof(user2)));
		fsync(ofd);		
	}	


return 0;
}
