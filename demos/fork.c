#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
void test(){
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
}
void test2(){
    printf("before!\n");
    int i=0;
    for(;i<5;i++){
        if(fork() == 0){
            break;
        }
    }
    if(i == 5){
        sleep(5);
        printf("father\n");
    }else{
        sleep(i);
        printf("son id : %d,parent: %d\n",getpid(),getppid());
    }
    exit(EXIT_SUCCESS);
}
    int num  =1 ;
void test3(){
    if(fork() == 0){
        //son
        sleep(2); // 等待父进程先执行
        printf("son num: %d\n",num); // 1
        num = 10; 
        printf("son num: %d\n",num); // 10
    }else{
        printf("fat num: %d\n",num); // 1
        num =20;
        printf("fat num: %d\n",num); // 20


        sleep(3);

    }
        printf("num: %d\n",num); // 1
    
    printf("over\n");
}
int main(){
    
    test3();
    return 0;
}