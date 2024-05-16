#include <iostream>
#include <future>
#include <thread>

void calculate_sum(std::promise<int>&& promise, int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    int result = a + b;
    promise.set_value(result);
}

int main() {
    std::promise<int> promise;

    std::future<int> future = promise.get_future();

    std::thread t(calculate_sum, std::move(promise), 5, 7);

    std::cout << "Doing other work in the main thread...\n";

    int sum = future.get();
    std::cout << "Result from promise: " << sum << std::endl;

    t.join();

    return 0;
}
