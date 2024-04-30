#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define READERS_COUNT 5
#define WRITERS_COUNT 3

pthread_rwlock_t rwlock;

// 模拟共享资源
int shared_data = 0;

void *reader(void *arg) {
    long tid = (long)arg;
    printf("读线程 %ld 尝试获取读锁...\n", tid);
    pthread_rwlock_rdlock(&rwlock);  // 获取读锁
    printf("读线程 %ld 已获取读锁。\n", tid);
    // 读取数据
    printf("读线程 %ld: 共享数据 = %d\n", tid, shared_data);
    usleep(100000);  // 短暂休眠，模拟读取数据的过程
    pthread_rwlock_unlock(&rwlock);  // 释放锁
    printf("读线程 %ld 释放读锁。\n", tid);
    return NULL;
}

void *writer(void *arg) {
    long tid = (long)arg;
    printf("写线程 %ld 尝试获取写锁...\n", tid);
    pthread_rwlock_wrlock(&rwlock);  // 获取写锁
    printf("写线程 %ld 已获取写锁。\n", tid);
    // 修改数据
    shared_data++;
    printf("写线程 %ld 更新数据为 %d\n", tid, shared_data);
    usleep(200000);  // 短暂休眠，模拟写入数据的过程
    pthread_rwlock_unlock(&rwlock);  // 释放锁
    printf("写线程 %ld 释放写锁。\n", tid);
    return NULL;
}

int main() {
    pthread_t readers[READERS_COUNT], writers[WRITERS_COUNT];
    long i;

    // 初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);

    // 创建读线程
    for (i = 0; i < READERS_COUNT; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)i);
    }

    // 创建写线程
    for (i = 0; i < WRITERS_COUNT; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)i);
    }

    // 等待所有线程完成
    for (i = 0; i < READERS_COUNT; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < WRITERS_COUNT; i++) {
        pthread_join(writers[i], NULL);
    }

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
