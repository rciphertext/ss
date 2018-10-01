// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8080 

#include "user_struct.c"
#include "admin_auth.c"
#include "admin_process.c"
#include "user_auth.c"
#include "user_process.c"

void clear(char out[])
{
	memset(out, 0,1024);
}



int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 5) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	
	while(1)
	{
			if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0) 
			{ 
				perror("accept"); 
				exit(EXIT_FAILURE); 
			} 

			if(!fork())
			{
				close(server_fd);
				
				//start point

				 int login_status=0;

					
					char *out="Select category 1.Admin 2.User 3.Joint user";	
					send(new_socket,out, strlen(out),0);	
					
					int cat=-1;
					read( new_socket,&cat,sizeof(cat));
					printf("%d\n",cat );


					char userid[100]={0};
					char pass[100]={0};

				while(login_status==0)
				{	
					out="Enter Userid and Password :";	
					send(new_socket,out, strlen(out),0); 	


					read( new_socket,&userid,sizeof(userid));
					read( new_socket,&pass,sizeof(pass));

					printf("%s\n",userid );
					printf("%s\n",pass );

					if(cat==1)
					{
						login_status=admin_authentication(userid,pass); //admin_auth.c
					}	
					if(cat==2 || cat==3)
					{
						login_status=user_authentication(userid,pass);
					}

					send(new_socket,&login_status, sizeof(login_status),0);	
				}	
					int a_set=0;
					int u_set=0;	
					switch(cat)
					{
						case 1://admin authentication
						
						//while(a_set==0)
						//{
								//read( new_socket,&userid,sizeof(userid));
								//read( new_socket,&pass,sizeof(pass));
								
								//printf("%s\n",userid );
								//printf("%s\n",pass );	


								login_status=admin_authentication(userid,pass); //admin_auth.c

								//send(new_socket,&login_status, sizeof(login_status),0);

								if(login_status==1)
								{
									//clear(out);
									while(login_status!=-1)
									{
										out="Login Successful !! operations allowed :1)add 2)search 3)exit ";	
										send(new_socket,out, strlen(out),0);

										int op;
										read( new_socket,&op,sizeof(op));
										printf("Operation selected is :%d\n",op);

										admin_operation(&new_socket,&op,&login_status); //admin_process.c
										//printf("---login_status%d\n",login_status );	

										if(op==3)
										{
											login_status=-1;
										}
									}

									//a_set=-2;
								}
							
						//}		
								break;
						case 2: //user authentication
							
						//while(u_set==0)
						//{
								//read( new_socket,&userid,sizeof(userid));
								//read( new_socket,&pass,sizeof(pass));

								//printf("%s\n",userid );
								//printf("%s\n",pass );	


								login_status=user_authentication(userid,pass);
								//send(new_socket,&login_status, sizeof(login_status),0);
								//printf("%d\n",login_status);

								if(login_status==2)
								{
									
									while(login_status!=-1)
									{
										out="Login Successful !! Allowed Operations :1)Deposit 2)Withdraw 3)Balance Enquiry 4)Password Change 5)View Detail 6)Exit";
										send(new_socket,out, strlen(out),0);
										int op;
										read( new_socket,&op,sizeof(op));
										printf("Operation selected is :%d\n",op);

										user_operation(&new_socket,&op,userid,pass,&login_status);  //user_process.c

										if(op==6)
										{
											login_status=-1;
										}
									}

									//u_set=-2;
								//}

						}		
								break;

						case 3: 
								login_status=user_authentication(userid,pass);
								//send(new_socket,&login_status, sizeof(login_status),0);
								printf("%d\n",login_status );

								if(login_status==2)
								{
									
									while(login_status!=-1)
									{
										out="Login Successful !! Allowed Operations :1)Deposit 2)Withdraw 3)Balance Enquiry 4)Password Change 5)View Detail 6)Exit";
										send(new_socket,out, strlen(out),0);
										int op;
										read( new_socket,&op,sizeof(op));
										printf("Operation selected is :%d\n",op);

										user_operation(&new_socket,&op,userid,pass,&login_status);  //user_process.c

										if(op==6)
										{
											login_status=-1;
										}
									}

								}			
						break;		
					}

						
					//while(1);								
				//end point	
				if(login_status==-1)
				{
					printf("PROCESS IS ABOUT TO EXIT... ... ...\n");
				}
				exit(0);
			} 
			else
			{
				close(new_socket);
			}
	}
	
	return 0; 
} 
