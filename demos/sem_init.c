#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ITEMS 10 // 缓冲区能够存储的最大产品数量
#define PRODUCERS 5  // 生产者数量
#define CONSUMERS 5  // 消费者数量

sem_t emptySlots;   // 用于记录生产者可以生产的槽数量
sem_t products;    // 用于记录消费者可以消费的产品数量
int buffer[MAX_ITEMS]; // 缓冲区
int in = 0;            // 缓冲区的生产位置
int out = 0;           // 缓冲区的消费位置

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* producer(void* arg) {
    sem_wait(&emptySlots); // 消费一个空槽位
    pthread_mutex_lock(&mutex);
    buffer[in] = rand() % 100 + 1; // 模拟生成产品
    printf("in index : %d\n",in);
    printf("Producer %d produced %d\n", *((int*)arg), buffer[in]);
    in = (in + 1) % MAX_ITEMS;
    pthread_mutex_unlock(&mutex);
    sem_post(&products); // 生成一个产品
    sleep(2); // 模拟生产时间
    return NULL;
}

void* consumer(void* arg) {
    sem_wait(&products); // 消耗一个产品
    pthread_mutex_lock(&mutex);
    int item = buffer[out];
    printf("out index : %d\n",out);
    printf("Consumer %d consumed %d\n", *((int*)arg), item);
    out = (out + 1) % MAX_ITEMS; // 更新消费位置
    pthread_mutex_unlock(&mutex);
    sem_post(&emptySlots); // 释放一个空槽位信号 生成一个空槽位
    sleep(1); // 模拟消费时间
    return NULL;
}

int main() {
    pthread_t pro[PRODUCERS], con[CONSUMERS];
    int producer_ids[PRODUCERS], consumer_ids[CONSUMERS];

    // 初始化信号量
    sem_init(&emptySlots, 0, MAX_ITEMS); // 初始化空槽位信号量为MAX_ITEMS
    sem_init(&products, 0, 0); // 初始化产品信号量为0

    // 创建生产者和消费者线程
    for(int i = 0; i < PRODUCERS; i++) {
        producer_ids[i] = i+1;
        pthread_create(&pro[i], NULL, producer, (void*)&producer_ids[i]);
    }
    for(int i = 0; i < CONSUMERS; i++) {
        consumer_ids[i] = i+1;
        pthread_create(&con[i], NULL, consumer, (void*)&consumer_ids[i]);
    }

    // 等待所有线程完成
    for(int i = 0; i < PRODUCERS; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < CONSUMERS; i++) {
        pthread_join(con[i], NULL);
    }

    // 销毁信号量
    sem_destroy(&emptySlots);
    sem_destroy(&products);
    pthread_mutex_destroy(&mutex);
    return 0;
}
