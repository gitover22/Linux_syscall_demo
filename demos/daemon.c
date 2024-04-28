#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
    pid_t ret = fork();
    if(ret == -1 ){
        perror("fork error" );
        exit(EXIT_FAILURE);
    }else if(ret == 0){
        printf("child process, my pid : %d\n",getpid());
        // 子进程成为守护进程的步骤
        // 1 . 创建会话 该子进程的pid会成为新创建的会话id，并且成为新会话的会话首进程
        if(setsid() == -1){
            perror("setsid error");
            exit(EXIT_FAILURE);
        }
        // 2. 修改工作目录
        if(chdir("/") == -1){
            perror("chdir error");
            exit(EXIT_FAILURE);
        }
        // 3. 修改文件权限掩码, 在open mkdir chmod等操作时，需要设置权限
        umask(0);
        // 关闭标准输入输出错误，使守护进程彻底脱离终端
        if(close(STDIN_FILENO) == -1){
            perror("close error");
            exit(EXIT_FAILURE);
        }
    
        // if(close(STDOUT_FILENO) == -1){
        //     perror("close error");
        //     exit(EXIT_FAILURE);
        // }
        if(close(STDERR_FILENO) == -1){
            perror("close error");
            exit(EXIT_FAILURE);
        }
        // 模拟子进程运行,如果关闭标准输出，那么就无法在终端看到输出
        while(1){
            printf("child process running\n");
            sleep(1);
        }
    }else{
        printf("parent process\n");
        sleep(1);
        printf("parent process exit\n");
        // 父进程退出
        exit(EXIT_SUCCESS);
    }
    return 0;
}