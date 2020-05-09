#include "threadpool.h"

ThreadPool::ThreadPool(size_t poolSize) : pool_is_active(true)
{
    for (size_t i = 0; i < poolSize; ++i)
    {
        threads.emplace_back([this]() {
            while (pool_is_active == true)
            {
                std::unique_lock<std::mutex> lock(mutex_);

                if (tasks.empty())
                {
                    queue_is_empty_.wait(lock);
                }
                else
                {
                    task cur_task = tasks.front();
                    tasks.pop();
                    lock.unlock();
                    cur_task();
                }
            }
        });
    }
}

ThreadPool::~ThreadPool()
{
    pool_is_active = false;
    queue_is_empty_.notify_all();
    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }
}