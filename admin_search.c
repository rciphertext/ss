
void search(int * n,struct detail *u,int *login_status)
{
	int new_socket=*n;

	printf("Username: %s\nAccount Number: %lu\n",u->username,u->acc_no);
	struct detail user;
	int count=0,set=0;
	int ofd = open("user_db.dat", O_RDWR, 0766);
	
	if(ofd == -1){printf("cannot open file");} 
	
	do{ 
		printf("read %d bytes:\n",count = read(ofd, &user, sizeof(user)));
		if(count !=0)
		{
			if(strcmp(u->username,user.username)==0 && (u->acc_no==user.acc_no))
			{
				set=1;
				break;
			} 
		}	
	}while(count != 0);	

	send(new_socket,&set, sizeof(set),0);


	char *out =NULL;
	if(set==1)
	{

		out="User found !! press 1).Deletion 2).Modification 3).Exit";
		send(new_socket,out, strlen(out),0);	

						int res;
						read( new_socket,&res,sizeof(res));

						lseek(ofd,(-1*sizeof(user)),SEEK_CUR); //taking pointer a struct back
						//read(ofd,&user,sizeof(user));
						
						struct flock fp;

					        fp.l_type=F_RDLCK;
					        fp.l_whence=SEEK_CUR;
					        fp.l_start=0;
					        fp.l_len=sizeof(u);
					        fp.l_pid=getpid();

					        //fcntl(ofd,F_GETLK,&fp);
						
						if(res==1)
						{
							//deletion selected
							
							memset(user.username,0,100);
							//lseek(ofd,(-1*sizeof(user)),SEEK_CUR); //taking pointer a struct back	

							//locking the data before deletion
							fp.l_whence=SEEK_CUR;
							fp.l_start=0;
					        fp.l_len=(100*sizeof(char));	
							fp.l_type=F_WRLCK;	

							fcntl(ofd,F_SETLKW,&fp);	
							
							write(ofd,&user,sizeof(user));	

							lseek(ofd,(-1*sizeof(user)),SEEK_CUR);

							fp.l_type=F_UNLCK;	
							fcntl(ofd,F_SETLKW,&fp);

							out="User deleted !!";
							send(new_socket,out, strlen(out),0);	
						}
						if(res==2)
						{
							//modification selected
							out="Select for modification :1.username 2.password 3.account number 4.Balance 5.Name";
							send(new_socket,out, strlen(out),0);

							int mod;
							read( new_socket,&mod,sizeof(mod));
							
							out="Enter new value";
							send(new_socket,out, strlen(out),0);

							//lseek(ofd,(-1*sizeof(user)),SEEK_CUR); //taking pointer a struct back	
							switch(mod)
								{
									case 1:read( new_socket,user.username,sizeof(user.username));
											
											break;	
									case 2:read( new_socket,user.password,sizeof(user.password));
										   
										   break;
									case 3:read( new_socket,&user.acc_no,sizeof(user.acc_no));
											
											break;
									case 4:read( new_socket,&user.balance,sizeof(user.balance));
										   
										   break;
									case 5:read( new_socket,&user.name,sizeof(user.name));
										   
										   break;
								}		

								
								printf("Username: %s\npassword: %s\naccountno: %lu\nbalance: %lu\nname: %s\n",user.username,user.password,user.acc_no,user.balance,user.name);
								fp.l_whence=SEEK_CUR;
								fp.l_start=0;
					        	fp.l_len=sizeof(user);	
								fp.l_type=F_WRLCK;	
								
								fcntl(ofd,F_SETLKW,&fp);

								write(ofd,&user,sizeof(user));

								lseek(ofd,(-1*sizeof(user)),SEEK_CUR);

								fp.l_type=F_UNLCK;	
								fcntl(ofd,F_SETLKW,&fp);

								out="Value Modified !!";
								send(new_socket,out, strlen(out),0);
									
						}

						if(res==3)
						{
							*login_status=-1;	
						}
		//return 0;
	}
	else
	{
		out="User NOT found !!";
		send(new_socket,out, strlen(out),0);
		//return -1;
	}
}
