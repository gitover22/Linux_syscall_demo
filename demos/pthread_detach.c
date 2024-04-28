#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
void *thread_func(void *arg)
{
    int i = 0;
    while(1){
        if(i++ == 10) break;
        sleep(1);
        printf("thread_func is running,tid = %lu\n",pthread_self());
    }
    return NULL;
}
int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_func, NULL);
    if (ret != 0)
    {
        printf("pthread_create error\n");
    }
    ret = pthread_detach(tid);
    if (ret != 0)
    {
        printf("pthread_detach error\n");
        exit(EXIT_FAILURE);
    }
    pthread_exit(NULL);//退出主线程
    return 0; // 如果执行了main函数的return，那么就会回收资源，创建的线程也被释放了
}