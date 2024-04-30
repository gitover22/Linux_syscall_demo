#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/*
 * 定义一个错误处理宏，当调用pthread函数出错时，设置errno，打印错误信息，并退出程序。
 */
#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

/*
 * 显示线程属性。
 * 参数:
 *   attr - 指向线程属性对象的指针。
 *   prefix - 打印每行属性信息前的前缀字符串。
 */
static void
display_pthread_attr(pthread_attr_t *attr, char *prefix)
{
    int s, i;
    size_t v;
    void *stkaddr;
    struct sched_param sp; // 描述线程调度参数的结构体

    // 获取并显示线程的分离状态
    s = pthread_attr_getdetachstate(attr, &i);  // 获取线程的分离状态 由传出参数i中返回
    if (s != 0)
        handle_error_en(s, "pthread_attr_getdetachstate");

    // 显示线程的分离状态
    printf("%sDetach state        = %s\n", prefix,
            (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
            (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
            "???");

    // 获取并显示线程的作用域
    s = pthread_attr_getscope(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getscope");
    // 显示线程的作用域
    printf("%sScope               = %s\n", prefix,
            (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
            (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
            "???");

    // 获取并显示线程的调度策略继承性
    s = pthread_attr_getinheritsched(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getinheritsched");
    // 显示线程的调度策略继承性
    printf("%sInherit scheduler   = %s\n", prefix,
            (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
            (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
            "???");
    
    // 获取并显示线程的调度策略
    s = pthread_attr_getschedpolicy(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getschedpolicy");
    printf("%sScheduling policy   = %s\n", prefix,
            (i == SCHED_OTHER) ? "SCHED_OTHER" :
            (i == SCHED_FIFO)  ? "SCHED_FIFO" :
            (i == SCHED_RR)    ? "SCHED_RR" :
            "???");

    // 获取并显示线程的调度优先级
    s = pthread_attr_getschedparam(attr, &sp);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getschedparam");
    printf("%sScheduling priority = %d\n", prefix, sp.sched_priority);

    // 获取并显示线程栈的保护大小
    s = pthread_attr_getguardsize(attr, &v);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getguardsize");
    printf("%sGuard size          = %zu bytes\n", prefix, v);

    // 获取并显示线程栈的地址和大小
    s = pthread_attr_getstack(attr, &stkaddr, &v);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getstack");
    printf("%sStack address       = %p\n", prefix, stkaddr);
    printf("%sStack size          = %#zx bytes\n", prefix, v);
}

/*
 * 线程启动函数，打印当前线程的属性。
 * 参数:
 *   arg - 传递给线程的参数，此函数中未使用。
 * 返回值:
 *   返回一个指向线程函数的指针。
 */
static void *
thread_start(void *arg)
{
    int s;
    pthread_attr_t gattr;

    /* 获取当前线程的属性（GNU扩展） */
    s = pthread_getattr_np(pthread_self(), &gattr);
    if (s != 0)
        handle_error_en(s, "pthread_getattr_np");

    printf("Thread attributes:\n");
    display_pthread_attr(&gattr, "\t");

    exit(EXIT_SUCCESS);         /* 终止所有线程 */
}

/*
 * 主函数，创建一个线程并显示其属性。
 * 参数:
 *   argc - 命令行参数的数量。
 *   argv - 命令行参数的值。
 * 返回值:
 *   返回程序执行的结果（0为成功，非0为失败）。
 */
int
main(int argc, char *argv[])
{
    pthread_t thr;
    pthread_attr_t attr;
    pthread_attr_t *attrp;      /* NULL或&attr */
    int s;

    attrp = NULL;

    /* 如果提供了命令行参数，使用它来设置线程栈大小属性，并设置其他几个线程属性，
     * 并设置attrp指向线程属性对象。 */
    if (argc > 1) {
        size_t stack_size;
        void *sp;

        attrp = &attr;

        // 初始化线程属性
        s = pthread_attr_init(&attr);
        if (s != 0)
            handle_error_en(s, "pthread_attr_init");

        // 设置线程的分离状态, PTHREAD_CREATE_DETACHED 是一个宏，表示创建的线程为分离状态
        s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (s != 0)
            handle_error_en(s, "pthread_attr_setdetachstate");

        // 设置线程调度策略的继承性 PTHREAD_EXPLICIT_SCHED 是一个宏，表示线程调度策略的继承性
        // 这意味着创建的线程将具有独立于其创建者线程的调度策略和优先级
        s = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        if (s != 0)
            handle_error_en(s, "pthread_attr_setinheritsched");

        // 将命令行参数转换为栈大小，并进行内存对齐
        stack_size = strtoul(argv[1], NULL, 0);
        s = posix_memalign(&sp, sysconf(_SC_PAGESIZE), stack_size);  //分配到的空间首地址由传出参数sp返回
        if (s != 0)
            handle_error_en(s, "posix_memalign");

        printf("posix_memalign() allocated at %p\n", sp); // 也就是后续栈空间首地址

        // 设置线程栈
        s = pthread_attr_setstack(&attr, sp, stack_size); // 给属性attr设置栈空间的属性，起始地址设为sp，空间大小为stack_size   
        if (s != 0)
            handle_error_en(s, "pthread_attr_setstack");
    }

    // 创建线程 创建线程的时候，把前面设置的pthread_attr_t 类型的变量传递进去
    s = pthread_create(&thr, attrp, &thread_start, NULL);
    if (s != 0)
        handle_error_en(s, "pthread_create");

    // 如果使用了线程属性对象，销毁它
    if (attrp != NULL) {
        s = pthread_attr_destroy(attrp);
        if (s != 0)
            handle_error_en(s, "pthread_attr_destroy");
    }

    pause();    /* 等待其他线程的退出 */
}