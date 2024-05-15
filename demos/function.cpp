#include <iostream>
#include <functional>
#include <vector>

void function() {
    std::cout << "Hello from a regular function!" << std::endl;
}
int sum_(int a,int b){
    return a+b;
}
int main() {
    // void(): 返回值为void, 无参数
    std::vector<std::function<void()>> tasks;
    std::vector<std::function<int(int,int)>> num_tasks;

    tasks.push_back(function);
    num_tasks.push_back(sum_);
    tasks.push_back([]() {
        std::cout << "Hello from a lambda expression!" << std::endl;
    });
    num_tasks.push_back([](int a,int b)->int {
        return a-b;
    });

    for (auto& task : tasks) {
        task();  // 调用存储的函数
    }


    for(auto &func:num_tasks){
        int num = func(5,3);
        std::cout<<num<<std::endl;
        
    }

    return 0;
}
