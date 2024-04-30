#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define THREAD_NUM 5
/**
 * gdb 调试多线程程序
 * info threads ：展示所有线程
 * thread n ：切换到第n个线程
 * thread apply n command ：对第n个线程执行命令
 * bt ：打印当前线程的调用栈
 * 
*/


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 模拟共享数据
typedef struct shared_data
{
    int num;
    char* str;
}shared_data;

shared_data data = {
    .num = 0,
    .str = NULL
};
// 模拟读线程
void *read_function(void *argv){
    pthread_mutex_lock(&mutex);
    sleep(1);
    printf("read thread %ld read data: %d , read str: %s\n",pthread_self(), data.num,data.str);
    pthread_mutex_unlock(&mutex);
}

// 模拟写线程
void *write_function(void *argv){
    pthread_mutex_lock(&mutex);
    data.num++;
    sleep(1);
    char num_str[10];
    printf("write thread %ld write_data: %d\n", pthread_self(),data.num);
    sprintf(num_str, "%d", data.num); // 将整数转换为字符串
    strcat(data.str, " "); // 先加一个空格
    strcat(data.str, num_str); // 将转换后的整数字符串追加到 data.str 中
    pthread_mutex_unlock(&mutex);
}

int main(){
    data.str = (char *)malloc(sizeof(char) * 100);
    strcpy(data.str, "hello ");
    pthread_t read_thread[THREAD_NUM];
    pthread_t write_thread[THREAD_NUM];
    int i;
    for(i = 0; i < THREAD_NUM; i++){
        pthread_create(&read_thread[i], NULL, read_function,NULL);
        pthread_create(&write_thread[i], NULL, write_function, NULL);
    }
    // 等待所有线程结束
    for(i = 0; i < THREAD_NUM; i++){
        pthread_join(read_thread[i], NULL);
        pthread_join(write_thread[i], NULL);
    }
    printf("data.str: %s\n", data.str);
    free(data.str);
    pthread_mutex_destroy(&mutex);
    return 0;
}