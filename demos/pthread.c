#include <pthread.h>    // 引入pthread库，它是多线程编程的标准UNIX接口
#include <stdio.h>      // 标准输入输出头文件
#include <stdlib.h>     // 包含exit等系统函数

// 线程运行的函数
void *thread_function(void *arg) {
    printf("Hello from the thread!\n");
    printf("arg : %d\n",(*(int *)arg));
    return NULL;       // 线程返回NULL，表示没有特别的返回值
}

int main() {
    pthread_t thread_id;      // pthread_t类型是线程的ID类型
    int ret;
    int num  =100;
    int *p =&num;
    // 创建线程，传递thread_function作为线程函数
    ret = pthread_create(&thread_id, NULL, thread_function, (void *)p);
    if (ret != 0) {
        perror("pthread_create");  // 如果创建线程失败，输出错误信息
        exit(EXIT_FAILURE);
    }

    printf("Thread has been created with ID %ld\n", (long) thread_id);

    ret = pthread_join(thread_id, NULL); // 阻塞等待线程id为thread_id的线程结束
    if (ret != 0) {
        perror("pthread_join");   // 如果等待线程失败，输出错误信息
        exit(EXIT_FAILURE);
    }

    printf("Thread has finished execution\n");
    return 0;           // 主函数返回0，表示程序正常退出
}
