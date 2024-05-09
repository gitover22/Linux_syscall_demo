#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define CONSUMER_NUM 1
#define PRODUCER_NUM 2
// 条件变量condition必须要和互斥量mutex配合使用
// 定义全局条件变量 静态初试化
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct share_data
{
    /* data */
    int num;
    struct shard_data *next;
};

struct share_data *head = NULL;
// 消费者线程
void *consumer(void * argv){
    while(1){
        pthread_mutex_lock(&mutex);
        if(head == NULL){ // 等待生产者生产数据
            pthread_cond_wait(&cond,&mutex); // 先接触互斥锁，待到条件变量cond就绪后加上锁
        }
        struct share_data *temp = head;
        head = head->next;
        printf("consumer get data:%d\n",temp->num);
        
        pthread_mutex_unlock(&mutex);
        free(temp);
        sleep(1);
    }
    return NULL;
}
// 模拟生产者
void *producer(void * argv){
    while (1){
        struct share_data *temp = malloc(sizeof(struct share_data));
        temp->num = rand()%100;
        printf("producer produce data:%d\n",temp->num);
        pthread_mutex_lock(&mutex);
        // 头插法
        temp->next = head;
        head = temp;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond); //唤醒一个等待条件变量cond的线程
        // pthread_cond_broadcast(&cond); //唤醒所有等待条件变量cond的线程
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_t consumer_tid[CONSUMER_NUM];
    pthread_t producer_tid[PRODUCER_NUM];


    int i;
    for(i=0;i<CONSUMER_NUM;i++){
        pthread_create(&consumer_tid[i],NULL,consumer,NULL);
    }
    for(i=0;i<PRODUCER_NUM;i++){
        pthread_create(&producer_tid[i],NULL,producer,NULL);
    }
    // 阻塞等待线程结束
    for(i=0;i<CONSUMER_NUM;i++){
        pthread_join(consumer_tid[i],NULL);
    }
    for(i=0;i<PRODUCER_NUM;i++){
        pthread_join(producer_tid[i],NULL);
    }

    pthread_mutex_destroy(&mutex);

    pthread_cond_destroy(&cond);
    return 0;
}