// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "user_struct.c"
#define PORT 8080 

void admin_add(int * );
void admin_search(int *,int *);
void user_deposit(int *);
void user_withdraw(int *);
void user_BalEnquiry(int *);
void user_ChangePassword(int *);
void user_Detail(int *);

void clear(char ack[])
{
	memset(ack, 0,1024);
}

int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	
	int login_status=0;
	while(login_status!=-1)
	{
		//start point
		
		char ack[1024]={0};
		read(sock,ack,sizeof(ack));
		printf("%s\n",ack);

		//category
		int in;
		scanf("%d",&in);
		send(sock ,&in, sizeof(in) , 0 );

		//clear(ack);
		//read(sock,ack,sizeof(ack));
		//printf("%s\n",ack);
		//entering userid and password
		char userid[100]={0};
		char pass[100]={0};
		
		while(login_status==0)
		{
			clear(ack);
			read(sock,ack,sizeof(ack));
			printf("%s\n",ack);
			
			memset(userid,0,100);
			memset(pass,0,100);

			scanf("%s",userid);
			scanf("%s",pass);
			send(sock ,&userid, strlen(userid) , 0 );
			send(sock ,&pass, strlen(pass) , 0 );

			//receving login status
			read(sock,&login_status,sizeof(login_status));
			//printf("%d\n",login_status );
		}	
			//if(login_status!=0)
			//{
				//break;
			//}	
			//printf("Invalid Login renter \n");
		//}		
		while(1)
		{	
			if(login_status==1) //admin :user add
			{
				
				clear(ack);
				read(sock,ack,sizeof(ack));	
				printf("%s\n",ack);

					//operation selection
					int op;
					scanf("%d",&op);
					send(sock ,&op, sizeof(op) , 0 );
				
				if(op==1)
				{			
					//user add
					admin_add(&sock);
				}
				if(op==2)
				{
					//search
					admin_search(&sock,&login_status);
					
					if(login_status==-1)
					{
						break;
					}
				}

				if(op==3)
				{
					printf("Transaction Complete bye!\n");
					login_status=-1;
					break;
				}	
			}
			
			

			if(login_status==2)
			{
				clear(ack);
				read(sock,ack,sizeof(ack));	
				printf("%s\n",ack);

				//operation selection
					//printf("Enter op \n");
					int op;
					scanf("%d",&op);
					send(sock ,&op, sizeof(op) , 0 );

					if(op==1)
					{	
						//deposit
						user_deposit(&sock);
					}
					if(op==2)
					{
						//withdraw
						user_withdraw(&sock);
					}
					if(op==3)
					{
						//Balance Enquiry
						user_BalEnquiry(&sock);
					}	
					if(op==4)
					{
						//Change Password
						user_ChangePassword(&sock);
					}

					if(op==5)
					{
						//user detail
						user_Detail(&sock);
					}

					if(op==6)
					{
						printf("Transaction Complete bye!\n");
						login_status=-1;
						break;
					}
			}

			
		}
		//getchar();
		//end point
	}
	return 0; 
} 

void admin_add(int * s)
{
	int sock=*s;
	char ack[1024]={0};

		//enter detail
	
		clear(ack);
		read(sock,ack,sizeof(ack));
		printf("%s\n",ack);	

		struct detail user;
		scanf("%s",user.username);
		scanf("%s",user.password);
		scanf("%ld",&user.acc_no);
		scanf("%ld",&user.balance);
		scanf("%s",user.name);
		//scanf("%s",user)
		send(sock ,&user, sizeof(user) , 0 );

		clear(ack);
		read(sock,ack,sizeof(ack));
		printf("%s\n",ack);	
}


void admin_search(int *s,int * login_status)
{
	int sock=*s;
	char ack[1024]={0};
	clear(ack);
	read(sock,ack,sizeof(ack));	
	printf("%s\n",ack);

	struct detail user;

	scanf("%s",user.username);
	scanf("%lu",&user.acc_no);
	//user.password=NULL;
	//user.balance=00000;
	//user.name=NULL;
	send(sock ,&user, sizeof(user) , 0 );

	int st;		//status if user present(1) or not(0);
	read(sock,&st,sizeof(st));

	clear(ack);
	read(sock,ack,sizeof(ack));
	printf("%s\n",ack);

	if(st==1)
	{
		int res;
		scanf("%d",&res);
		send(sock ,&res, sizeof(res) , 0 ); //Y/N want to delete or not

		if(res==1)
		{
			//deletion
			clear(ack);
			read(sock,ack,sizeof(ack));
			printf("%s\n",ack);
		}
		if(res==2)
		{
			//modification
			clear(ack);
			read(sock,ack,sizeof(ack));
			printf("%s\n",ack);

			int mod;
			scanf("%d",&mod);
			send(sock ,&mod, sizeof(mod) , 0 );

			clear(ack);
			read(sock,ack,sizeof(ack));
			printf("%s\n",ack);

			char str[100];
			unsigned long val;

			switch(mod)
			{
				case 1:	
				case 2:scanf("%s",str);
					   send(sock ,str, sizeof(str) , 0 );
					   break;
				case 3:
				case 4:scanf("%lu",&val);
					   send(sock ,&val, sizeof(val) , 0 );
					   break;
				case 5:scanf("%s",str);
					   send(sock ,str, sizeof(str) , 0 );
					   break;
			}

			
			clear(ack);
			read(sock,ack,sizeof(ack));
			printf("%s\n",ack);
		}

		if(res==3)
			{
				printf("Transaction Complete bye!\n");
				*login_status=-1;

			}	
	}
}


void user_deposit(int *s)
{
	int sock=*s;
	char ack[1024]={0};

	clear(ack);
	read(sock,ack,sizeof(ack));  //wait...	
	printf("%s\n",ack);

	clear(ack);
	read(sock,ack,sizeof(ack));  //amount asked	
	printf("%s\n",ack);

	unsigned long amount=0UL;
	scanf("%lu",&amount);
	send(sock ,&amount, sizeof(amount) , 0 );

	clear(ack);
	read(sock,ack,sizeof(ack));  //wait...	
	printf("%s\n",ack);

	amount=0UL;	
	read(sock,&amount,sizeof(amount));  //wait...	
	printf("%lu\n",amount);
}

void user_withdraw(int *s)
{
	int sock=*s;
	char ack[1024]={0};

	clear(ack);
	read(sock,ack,sizeof(ack));  //wait...	
	printf("%s\n",ack);

	clear(ack);
	read(sock,ack,sizeof(ack));  //amount asked for withdraw	
	printf("%s\n",ack);

	unsigned long amount=0UL;
	scanf("%lu",&amount);
	send(sock ,&amount, sizeof(amount) , 0 );

	clear(ack);
	read(sock,ack,sizeof(ack));  
	printf("%s\n",ack);

	amount=0UL;	
	read(sock,&amount,sizeof(amount));  	
	printf("%lu\n",amount);
}

void user_BalEnquiry(int *s)
{
	int sock=*s;
	char ack[1024]={0};

	clear(ack);
	read(sock,ack,sizeof(ack));  //wait...	
	printf("%s\n",ack);

	unsigned long amount=0UL;

	clear(ack);
	read(sock,ack,sizeof(ack));  	
	printf("%s\n",ack);
	
	read(sock,&amount,sizeof(amount));  	
	printf("%lu\n",amount);		
}

void user_ChangePassword(int *s)
{
	int sock=*s;
	char ack[1024]={0};

	clear(ack);
	read(sock,ack,sizeof(ack));  //wait...	
	printf("%s\n",ack);

	clear(ack);
	read(sock,ack,sizeof(ack));  //ask to enter new password
	printf("%s\n",ack);

	char p[100];
	scanf("%s",p);
	send(sock ,p,sizeof(p) , 0 );
}

void user_Detail(int *s)
{
	int sock=*s;
	char ack[1024]={0};

	clear(ack);
	read(sock,ack,sizeof(ack));  //wait...	
	printf("%s\n",ack);

	clear(ack);
	read(sock,ack,sizeof(ack));  //show detail
	printf("%s\n",ack);

	char p[100];
	read(sock,p,sizeof(p));  
	printf("%s\n",p);	
}
/*getchar();
		send(sock , hello , strlen(hello) , 0 ); 
		printf("Hello message sent\n"); 
		valread = read( sock , buffer, 1024); 
		printf("%s\n",buffer ); 
		getchar();
		*/
