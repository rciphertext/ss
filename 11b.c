 #include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{

    int fd1 = open("input.txt", O_WRONLY | O_APPEND);

    if(fd1 < 0)
        printf("Error\n");

    int fd2 = dup2(fd1,0);
    char* str1="original file";
        char * str2 ="newfile" ;

    printf("%d %d",fd1,fd2);
    return 0;
}

