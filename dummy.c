#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "user_struct.c"

int main(){
	
	
	struct detail user;
	int count=0,set=0;
	int ofd = open("user_db.dat", O_RDONLY, 0766);
	
	if(ofd == -1){printf("cannot open file");} 
	
	//do{ 
		 read(ofd, &user, sizeof(user));

		printf("Username: %s\nPassword: %s\nAccount Number: %ld\nAccount Balance %ld\nName :%s\n", user.username, user.password,user.acc_no,user.balance,user.name); 
		//lseek(ofd,(-1*sizeof(user)),SEEK_CUR); //taking pointer a struct back  
		read(ofd, &user, sizeof(user));	
		printf("Username: %s\nPassword: %s\nAccount Number: %ld\nAccount Balance %ld\nName :%s\n", user.username, user.password,user.acc_no,user.balance,user.name); 
	//}while(count != 0);	
return 0;
}
