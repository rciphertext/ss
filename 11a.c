 #include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{

    int fd1 = open("input.txt", O_WRONLY | O_APPEND);

    if(fd1 < 0)
        printf("Error\n");

    int fd2 = dup(fd1);
    char* str1="original file";
        char * str2 ="newfile" ;

    write(fd1,str1, strlen(str1));

    write(fd2,str2, strlen(str2));

    return 0;
}

