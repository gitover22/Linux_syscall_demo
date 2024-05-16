#include <iostream>
#include <future> // std::async
#include <thread>

void task(){
    std::cout << "task running" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "task end" << std::endl;
}

int main()
{
    // 异步调用 task 函数
    std::future<void> result = std::async(std::launch::async, task);
    std::cout << "doing some work" << std::endl;
    result.get();  // 阻塞等待异步任务完成
    std::cout << "main function end" << std::endl;
    return 0;
}
