#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
int main()
{
    pid_t pid;
    int fd[2]; // 0:读端，1:写端
    if (pipe(fd) < 0)
    {
        perror("pipe error");
        return -1;
    }
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]); // 关闭读端
        printf("child writing \n");
        write(fd[1], "hello", strlen("hello"));
        close(fd[1]);
    }
    else if(pid > 0)
    {
        close(fd[1]); // 关闭写端
        char buf[1024];
        read(fd[0], buf, 1024);
        printf("parent read:%s\n", buf);
        close(fd[0]);
    }else{
        perror("fork error");
    }
    return 0;
}