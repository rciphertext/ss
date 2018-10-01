

void user_operation(int * n,int * op,char * userid,char * pass,int * login_status)
{
	int new_socket=*n;
	char *out=NULL;
	struct detail u;

	//searching for data

	int count=0;
	int ofd = open("user_db.dat",O_RDWR, 0766);

	if(ofd == -1){printf("cannot open user_db.dat file");}
	
	while((count=read(ofd, &u, sizeof(u)))!=0)
	{
		if((strcmp(userid,u.username)==0) && (strcmp(pass,u.password)==0))
		{		
			break;
		}
	}

	lseek(ofd,(-1*sizeof(u)),SEEK_CUR);

	struct flock fp;

        fp.l_type=F_RDLCK;
        fp.l_whence=SEEK_CUR;
        fp.l_start=(200*sizeof(char));
        fp.l_len=sizeof(u);
        fp.l_pid=getpid();
        fcntl(ofd,F_GETLK,&fp);
        //printf("%d\n %d\n %ld\n %ld\n %d\n",fp.l_type,fp.l_whence,fp.l_start,fp.l_len,fp.l_pid);

	//LOCKING THE FILE
        out="Wait...";
		send(new_socket,out, strlen(out),0);
		

	switch(*op)
	{
		case 1 ://Deposit
				fp.l_type=F_WRLCK;	
				fcntl(ofd,F_SETLKW,&fp);
				out="Enter amount you want to Deposit";
				send(new_socket,out, strlen(out),0);
				
				unsigned long amount=0;
				read( new_socket,&amount,sizeof(amount));

				printf("Amount entered :%lu\n",amount);	
					
				printf("old amount :%lu\n", u.balance);
				u.balance=u.balance+amount; //updated amount
					
				
				write(ofd,&u,sizeof(u));

				out="Balance Updated !! New Balance :";
				send(new_socket,out, strlen(out),0);

				send(new_socket,&u.balance, sizeof(u.balance),0);
				lseek(ofd,(-1*sizeof(u)),SEEK_CUR);

				break;
		case 2 ://Withdraw
				fp.l_type=F_WRLCK;	
				fcntl(ofd,F_SETLKW,&fp);

				out="Enter amount you want to Withdraw";
				send(new_socket,out, strlen(out),0);

				unsigned long w_amount=0,old_amount=0;
				read( new_socket,&w_amount,sizeof(w_amount));
				printf("Withdraw amount %lu\n",w_amount);
				
				if(u.balance<=w_amount)
				{
					//u.balance=old_amount;
					write(ofd,&u,sizeof(u));
					out="*Not enough Balance* Available Balance :";
					send(new_socket,out, strlen(out),0);
					send(new_socket,&u.balance, sizeof(u.balance),0);
						
				}
				else
				{
					printf("old amount :%lu\n", u.balance);
					u.balance=(long)(u.balance-w_amount); //updated amount
					printf("New amount :%lu\n", u.balance);	

					write(ofd,&u,sizeof(u));
					out="Balance Updated !! New Balance :";
					send(new_socket,out, strlen(out),0);
					send(new_socket,&u.balance, sizeof(u.balance),0);
				}	

				lseek(ofd,(-1*sizeof(u)),SEEK_CUR);
				break;	
		case 3  ://Balance Enquiry
					fp.l_type=F_RDLCK;	
					fcntl(ofd,F_SETLKW,&fp);

					out="Available Balance :";
					send(new_socket,out, strlen(out),0);
					send(new_socket,&u.balance, sizeof(u.balance),0);
				break;
		case 4 ://Change Password
					fp.l_type=F_WRLCK;	
					fcntl(ofd,F_SETLKW,&fp);

					out="Enter New Password :";
					send(new_socket,out, strlen(out),0);

					read( new_socket,u.password,sizeof(u.password));

					printf("New Password :%s\n",u.password );
					write(ofd,&u,sizeof(u));

					lseek(ofd,(-1*sizeof(u)),SEEK_CUR);	
				break;
		case 5://view Detail
					fp.l_type=F_RDLCK;	
					fcntl(ofd,F_SETLKW,&fp);

					out="Detail :";
					send(new_socket,out, strlen(out),0);
					send(new_socket,u.name, sizeof(u.name),0);
				break;
		case 6://Exit
				*login_status=-1;
				break;												
	}

	fp.l_type=F_UNLCK;
	fcntl(ofd,F_SETLKW,&fp);
}
