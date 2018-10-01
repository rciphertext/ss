int writeback(struct detail * u) {     

	struct detail user=*u;
	printf("Username: %s\nPassword: %s\nAccount Number: %ld\nAccount Balance %ld\nName :%s\n",     u->username, u->password,u->acc_no,u->balance,u->name);  

   int ofd = open("user_db.dat",O_WRONLY | O_APPEND | O_CREAT, 0766);
	
	if(ofd == -1){printf("cannot open file");}
	else{
		printf("written %ld bytes:",write(ofd,&user,sizeof(user)));
		fsync(ofd);		
	}

	if(ofd==-1)
	{
		return -1;
	}
	else
	{
		return 0;
	}	
}
