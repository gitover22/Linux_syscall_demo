#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
// 信号处理函数
void signal_handler(int signal_number) {
    printf("捕获到信号 (%d)，但不退出\n", signal_number);
}

int main() {
    struct sigaction sa;
    
    // 清空信号处理结构体，并设置信号处理函数
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    
    // 使用SA_RESTART标志，使得被信号中断的系统调用可以自动重启
    sa.sa_flags = SA_RESTART;

    // 设置SIGINT的处理行为
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    // 设置SIGBUS的处理行为
    if (sigaction(SIGBUS, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }
    // 主循环，模拟长时间运行的程序
    while (1) {
        printf("程序运行中，按 Ctrl+C 测试信号捕捉。\n");
        sleep(1);  // 暂停1秒，模拟程序正在处理其他事务
    }

    return 0;
}
