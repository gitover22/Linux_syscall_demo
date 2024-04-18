// #include <iostream>
#include<unistd.h>
#include <stdlib.h>
#include<memory>
// #include "pthread.h"
#include "_huafeng.h"
// 单例中的懒汉模式，是指调用getInstance时才进行实例化对象
// 饿汉模式，则是编译阶段就创建好了，get_Instance不需要实例化对象
class signal_Class{
public:
    static signal_Class* Get_instance(); // 声明
private:
    static signal_Class * p; // 静态指针变量,静态成员变量
    static pthread_mutex_t __mutex; // 静态锁，因为静态成员函数只能访问静态成员变量
    signal_Class(){ // 私有化构造函数，防止实例化，实现单例模式
        pthread_mutex_init(&__mutex,NULL);   // 互斥锁的初试化
    }
    ~signal_Class(){};
};
// 获取函数的定义
signal_Class* signal_Class::Get_instance(){
    if(p==NULL){
        pthread_mutex_lock(&__mutex);
        p=new signal_Class;
        pthread_mutex_unlock(&__mutex);
    }
    return p;
}
signal_Class* signal_Class::p=NULL;
pthread_mutex_t signal_Class::__mutex = PTHREAD_MUTEX_INITIALIZER;

// 更加优雅的方式
class signal{

private:
    signal(){};
    ~signal(){};
public:
    static signal* Get_instance();
};
signal* signal::Get_instance(){
    static signal p; // 调用Get_instance时才会实例化，懒汉模式
    return &p;
}
// 饿汉模式

// 更加优雅的方式
class signal__{

private:
    signal__(){};
    ~signal__(){};
    static signal__* p;
public:
    static signal__* Get_instance();
};
signal__* signal__::Get_instance(){
    return p;
}
signal__* signal__::p=new signal__; // 编译阶段就初试化 饿汉模式

void tes_ptr() {
    std::shared_ptr<int> s_p = std::make_shared<int>(32);
    std::weak_ptr<int> w_p = s_p;
    const std::weak_ptr<int> &ptr = w_p; // ptr是w_p的引用
     // 使用 ptr 访问参数
    if (!ptr.expired()) {
        // 获取 shared_ptr
        std::shared_ptr<int> sharedPtr = ptr.lock();

        // 访问 shared_ptr 所指向的值
        if (sharedPtr) {
            std::cout << "Value accessed through weak_ptr: " << *sharedPtr << std::endl;

            // 查看 shared_ptr 的引用计数
            std::cout << "Reference count of shared_ptr: " << sharedPtr.use_count() << std::endl;
        } else {
            std::cout << "shared_ptr is null." << std::endl;
        }
    } else {
        std::cout << "weak_ptr has expired." << std::endl;
    }


    // std::shared_ptr<int> p = nullptr; // 定义一个 shared_ptr，初始化为空指针
    // int a[] = {1, 2, 3, 4, 5};

    // // 将 p 指向数组 a 的首地址
    // p = std::shared_ptr<int>(a, [](int*){});
    // std::cout<<a<<"  --  "<<p.get()<<std::endl;
    // // 通过指针 p 遍历数组，并通过 p 修改数组的内容
    // for (int i = 0; i < 5; ++i) {
    //     std::cout << "Element at index " << i << ": " << *(p.get() + i) << std::endl;
    //     *(p.get() + i) += 1; // 数组内容全部加1
    // }

    // // 重新定义一个指针也指向 p 的位置
    // std::shared_ptr<int> q(p);

    // // 输出修改后的数组内容
    // std::cout << "Modified array elements:" << std::endl;
    // for (int i = 0; i < 5; ++i) {
    //     std::cout << "Element at index " << i << ": " << *(q.get() + i) << std::endl;
    // }
}


int main(int argc,char *argv[])
{
    void test_fork();
    void test__();
    test__();



    // std::shared_ptr<int> ptr =std::make_shared<int>(12);
    // std::shared_ptr<int> p2 =ptr;
    // std::shared_ptr<int> p3 =std::move(ptr); // move之后，ptr就会变为空指针

    // print_NUM<int>(ptr.use_count());
    // // print_NUM(ptr.get()); //
    // if(ptr == nullptr)
    // std::cout<<"null"<<std::endl;

    // print_NUM<int>(p2.use_count());
    // print_NUM<int>(p3.use_count());
    // // tes_ptr();
    // signal tes1;
    // signal* p1 =signal::Get_instance();
    // signal* p2 =signal::Get_instance();
    // std::cout<<p1<<"  "<< p2<<std::endl;
    // int *test();
    // int * p = test();   
    // std::cout<<p<<std::endl;
    // std::cout<<*p<<std::endl;
    // signal__ * p1 =signal__::Get_instance();
    // signal__ * p2 =signal__::Get_instance();
    // if(p1  == p2)
    // std::cout<<true<<std::endl;
    // std::string * str = new std::string[12]; // 经测试，每一个string类型大小是32B
    // char * s = new char[12];
    // std::cout<<str<<std::endl;
    // for(int i=0;i<12;i++){
    //     str[i] = "helo + "+std::to_string(i);
    //     std::cout<<*(str + i)<<std::endl; // 解引用得到值
    // } 
    // std::cout<<&s<<std::endl;
    // for(int i=0;i<12;i++){
    //     s[i] = 'a'+i;
    //     std::cout<<s[i]<<std::endl; // 解引用得到值
    // }
    // delete[] str;
    // delete[] s;
    return 0;
}
int* test(){
    static int a=10;
    std::cout<<&a<<std::endl;
    return &a;
}

void test_fork(){
    printf("befork\n");
    int count =0 ;
    for (size_t i = 0; i < 3; i++)
    {
        pid_t ret = fork();
        if(ret == -1){
            perror("fork error");
        }else if(ret == 0){
            count++;
            printf("i am :%d",getpid());
        }
    }
    printf("共创建了%d个子进程\n",count);
}

void test__(){
    printf("before\n");
    for(int i =0;i<10;i++){
        pid_t ret = fork();
        if(ret == 0){
            printf("%d\n",getpid());
            break;
        }
    }
}