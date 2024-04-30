#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void *
thread_func(void *ignored_argument)
{
    int s;

    /* Disable cancellation for a while, so that we don't
        immediately react to a cancellation request */
    s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); // 设置可取消状态为disable,屏蔽掉线程的取消
    if (s != 0)
        handle_error_en(s, "pthread_setcancelstate");

    printf("thread_func(): started; cancellation disabled\n");
    sleep(5); // 在睡眠过程中，收到了主线程的取消请求，但是不会处理，因为前面设置了PTHREAD_CANCEL_DISABLE
    printf("thread_func(): about to enable cancellation\n");

    s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); // 设置可取消状态为enable,接受线程的取消
    if (s != 0)
        handle_error_en(s, "pthread_setcancelstate");

    /* sleep() is a cancellation point */
    sleep(1000);        // Should get canceled while we sleep  sleep() 函数是一个取消点，线程会在这里响应之前的取消请求。

    /* Should never get here */

    printf("thread_func(): not canceled!\n");
    return NULL;
}
int
main(void)
{
    pthread_t thr;
    void *res;
    int s;

    /* Start a thread and then send it a cancellation request */

    s = pthread_create(&thr, NULL, &thread_func, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_create");

    sleep(2);           /* Give thread a chance to get started */

    printf("main(): sending cancellation request\n");
    // pthread_cancel不会阻塞等待线程结束，它只是向线程发送一个取消信号。线程的取消与否依赖于它是否达到取消点(如sleep等)以及当时的取消状态设置
    s = pthread_cancel(thr); // pthread_cancel 发送一个取消请求给目标线程，但它本身并不会阻塞调用者，仅仅发送一个请求，然后立即返回
    if (s != 0)
        handle_error_en(s, "pthread_cancel");

    /* Join with thread to see what its exit status was */
    s = pthread_join(thr, &res);
    if (s != 0)
        handle_error_en(s, "pthread_join");

    if (res == PTHREAD_CANCELED)
        printf("main(): thread was canceled\n");
    else
        printf("main(): thread wasn't canceled (shouldn't happen!)\n");
    exit(EXIT_SUCCESS);
}