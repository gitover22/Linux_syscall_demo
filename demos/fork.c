#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()

{
    printf("fork之前的代码，子进程也会复制这部分代码，但没有执行的机会\n");

    pid_t ret  = fork(); // 创建子进程

    if(ret == -1){
        printf("创建失败\n");
        exit(EXIT_FAILURE);
    }else if(ret == 0){
        //子进程部分,父进程也有这部分代码,但是不会执行这部分代码
        printf("子进程在执行中。。子进程id为：%d，父进程id为：%d\n",getpid(),getppid());
        sleep(5);

    }else if(ret > 0){
        //父进程部分，子进程也会有这段代码，但是不会执行这部分代码
        printf("i am 父进程，子进程是：%d,我的父进程id为：%d\n",ret,getppid());
        sleep(5);
    }
    printf("父子进程都可以执行的部分\n");
    sleep(1000);

    return 0;
}