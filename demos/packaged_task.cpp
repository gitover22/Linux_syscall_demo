#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int add(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return a + b;
}

int main() {
    std::packaged_task<int(int, int)> task(add);

    std::future<int> result = task.get_future();

    std::thread t(std::move(task), 5, 7);

    std::cout << "Doing other work in the main thread...\n";

    int sum = result.get();
    std::cout << "Result from packaged_task: " << sum << std::endl;

    t.join();

    return 0;
}
