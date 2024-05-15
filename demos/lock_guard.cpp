/**
 * @brief 演示lock_guard的使用
*/

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


std::mutex mtx;
int shared_data = 0;
void func()
{
    std::lock_guard<std::mutex> lck(mtx); // 自动加锁 离开作用域自动解锁
    shared_data++;
    std::cout << shared_data << std::endl;
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        std::thread t(func);
        threads.push_back(std::move(t));
    }
    for (auto &t : threads)
    {
        t.join();
    }
    std::cout << shared_data << std::endl;
    return 0;
}