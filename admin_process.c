#include "admin_add.c"
#include "admin_search.c"
#include "admin_delete.c"

void admin_operation(int * n,int * op,int * l_status)
{
	int new_socket=*n;
	char *out=NULL;
	struct detail user;

	switch(*op)
	{
		case 1 ://add user
				//Cleanup: ;
				out="Enter 1.Userid 2.Password 3.Account Number 4.Account Balance 5.Name ";
				send(new_socket,out, strlen(out),0);

				
				read( new_socket,&user,sizeof(user));

				//writing this data back to file 

				int wb_status=writeback(&user); //admin_add.c

					if(wb_status==-1)
					{
						out="Unsuccessful";
					}
					else
					{
						out="Successful";
					}

					send(new_socket,out, strlen(out),0);

				break;
		case 2 ://search
				out="Enter Information for search : 1. userid 2. account number";
				send(new_socket,out, strlen(out),0);
				
				read( new_socket,&user,sizeof(user));
				printf("Username: %s\nAccount Number: %lu\n",user.username,user.acc_no);	
				//int s_status;
				search(&new_socket,&user,l_status); //admin_search.c

					/*if(s_status==0)
					{
						out="User found !! You want to delete it ? [Y/N]";
					}
					else
					{
						out="User NOT found !!";
					}

					send(new_socket,out, strlen(out),0);

					if(s_status==0)
					{
						char res;
						read( new_socket,&res,sizeof(res));

						if(res=='Y')
						{
							//deletion selected
							int d_status=deletion(&user);	
						}
					}
					*/
				break;	
		case 3  ://exit
				*l_status=-1;	
				break;				
	}

}
