int deletion(struct detail *u)
{
	struct detail user=*u;
	memset(user.username,0,100);

	int ofd = open("user_db.dat",O_WRONLY, 0766);

	if(ofd == -1){printf("cannot open file");}
	else
	{
		

		lseek(ofd,-1*sizeof(user),SEEK_CUR);

		write(ofd,&user,sizeof(user));

		return 0;		
	}	
	return -1;	
}
