/**
 * @brief 简单线程池实现
 * @author huafeng
*/
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <vector>
#include <functional>
class ThreadPool{
public:
    ThreadPool(int thread_num){
        for(int i = 0; i < thread_num; i++){
            pool.emplace_back([this](){
                while(true){
                    std::function<void()> task;
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this](){return stop || !tasks.empty();});
                    if(stop && tasks.empty()){ // 如果线程池，并且任务队列为空，则退出
                        return;
                    }
                
                    task = std::move(tasks.front());
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });

        }
    }
    ~ThreadPool(){
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for(auto& t : pool){
            t.join();
        }
    }
    template<class F, class... Args>
    void add_task(F&& f, Args&&... args){
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::lock_guard<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        cv.notify_one();
    }
private:
    std::vector<std::thread> pool;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;

};
int main()
{
    ThreadPool pool(5);
    for(int i = 0; i < 10; i++){
        pool.add_task([i](){
            std::cout << "runing task" << i << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "ending task" << i << std::endl;
        });
    }
    return 0;
}