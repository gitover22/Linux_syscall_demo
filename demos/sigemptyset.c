#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
/*
*  信号集操作函数
*  sigemptyset()  初始化信号集 全0
*  sigfillset()   将信号集初始化为全1 
*  sigaddset()    添加信号到信号集中 添1
*  sigdelset()    从信号集中删除信号 删1
*  sigismember()  判断信号是否在信号集中
*  sigprocmask()  修改信号集
*  sigpending()  查看当前进程的未决信号集
*/
void printSet(sigset_t *set)
{
    int i;
    for(i = 1; i < 30; i++)
    {
        if(sigismember(set, i))
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}
int main()
{
    int i;
    sigset_t set,pending;
    sigemptyset(&set); // 全0信号集
    sigaddset(&set, SIGINT); // 添加SIGINT信号
    sigaddset(&set, SIGALRM); // 添加SIGALRM信号
    sigaddset(&set, SIGBUS); // 添加SIGBUS信号
    
    int ret = sigprocmask(SIG_BLOCK, &set, NULL);
    if(ret == -1)
    {
        perror("sigprocmask");
        return -1;
    }
    while(1){
    // 获取未决信号集
    ret = sigpending(&pending);
    if(ret == -1){
        perror("sigpending");
        return -1;
    }
        sleep(1);
        printSet(&pending);
    }
    return 0;
 }