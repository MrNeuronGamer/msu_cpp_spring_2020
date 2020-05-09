#pragma once

#include <thread>
#include <future>
#include <queue>
#include <vector>
#include <functional>
#include <memory>
#include <condition_variable>

class ThreadPool
{
public:
    using task = std::function<void()>;
    using thread_vector = std::vector<std::thread>;
    using task_queue = std::queue<task>;

    explicit ThreadPool(size_t poolSize);

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {

        auto new_task = std::make_shared<std::packaged_task<decltype(func(args...))()>>([func, args...]() {
            return func(args...);
        });
        tasks.push([new_task]() {
            (*new_task)();
        });

        std::unique_lock<std::mutex> lock(mutex_);
        queue_is_empty_.notify_one();
        return new_task->get_future();
    }

    ~ThreadPool();

private:
    thread_vector threads;
    task_queue tasks;
    std::mutex mutex_;
    std::condition_variable queue_is_empty_;
    std::atomic_bool pool_is_active;
};