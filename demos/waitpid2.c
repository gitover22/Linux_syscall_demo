#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{   
    pid_t pid1,pid2;
    int status;
    for(int i=0;i<20;i++){
        if(fork() == 0)
        {    
            printf("i am child :%d\n",getpid());
            sleep(i);
            return i;
        }
    }
    while((pid2 = waitpid(-1,&status,WNOHANG)) != -1){
        printf("i am parent ,waiting for child exit\n");
        printf("child %d exit\n",pid2);
        if(WIFEXITED(status)){
            printf("child %d exit with %d\n",pid2,WEXITSTATUS(status)); // WEXITSTATUS(status)返回进程退出时的状态码 return value
        }
        sleep(1);
    }
    return 0;
}