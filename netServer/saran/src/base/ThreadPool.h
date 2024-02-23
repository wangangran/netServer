#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <deque>
#include <list>
#include <functional>
#include "base/Condition.h"
#include <memory>

namespace saran {

namespace base {

class Thread;

using Task = std::function<void()>;

class ThreadPool{
public:
    explicit ThreadPool();
    ~ThreadPool();

    int Init(int threadNum);
    void destroy();
    void pushTask(const Task &task);
    Task getTask();
    void doTask();
private:
    std::deque<Task> works_;
    std::list<std::unique_ptr<Thread>> threads_;   
    bool exit = false; 
    Mutex mutex_;
    Condition condition_;
};

}

}

#endif