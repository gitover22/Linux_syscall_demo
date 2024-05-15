/**
 * @brief 仅演示unique_lock的用法
*/
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
std::timed_mutex mtx;
int share_data = 0;
void func(){
    std::unique_lock<std::timed_mutex> lock(mtx,std::defer_lock);
    lock.try_lock_for(std::chrono::milliseconds(1));  // 尝试获取锁，最多等待1ms,1ms内没有获取到锁，则直接在无锁状态继续执行
    for(int i=0 ;i<1000000;i++)
        share_data++;
}   
int main(){
    std::thread t1(func);
    std::thread t2(func);
    std::thread t3(func);
    t1.join();
    t2.join();
    t3.join();
    std::cout << share_data << std::endl;
    return 0;
}

