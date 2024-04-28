#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// 信号处理函数
void signal_handler(int signal_number) {
    printf("捕获到信号 SIGINT (%d)，但不退出\n", signal_number);
    // 重新设置信号处理器，以捕捉后续的同类型信号
    signal(SIGINT, signal_handler);
}

int main() {
    // 设置 SIGINT 的处理函数
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        printf("无法设置信号处理器\n");
        return 1;
    }

    // 主循环，模拟长时间运行的程序
    while (1) {
        printf("程序运行中，按 Ctrl+C 测试信号捕捉。\n");
        sleep(1);  // 暂停1秒，模拟程序正在处理其他事务
    }

    return 0;
}
