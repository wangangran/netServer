#include "ThreadPool.h"
#include "base/Thread.h"
#include <iostream>

using namespace saran::base;
using namespace std;

ThreadPool::ThreadPool() : condition_(mutex_)
{

}

ThreadPool::~ThreadPool()
{
    destroy();
}

int ThreadPool::Init(int threadNum) 
{
    for (int i = 0; i < threadNum; ++i) {
        Thread *t = new Thread(bind(&ThreadPool::doTask, this), nullptr);
        if (nullptr != t) {
            t->start();
            threads_.push_back(unique_ptr<Thread>(t));
        }
    }

    return threads_.size();
}

void ThreadPool::destroy()
{
    exit = true;
    condition_.notifyAll();
    for (auto ite = threads_.begin(); ite != threads_.end(); ++ite) {
        (*ite)->join();
    }
}

void ThreadPool::pushTask(const Task &task)
{
    LockGuard<Mutex> lock(&mutex_);
    works_.push_back(task);
    condition_.notify();
}

Task ThreadPool::getTask()
{  
    LockGuard<Mutex> lock(&mutex_);
    while (works_.size() <= 0) {
        condition_.wait();  
    } 

    Task t = works_.at(0);
    works_.pop_front();
    return t;
}

void ThreadPool::doTask()
{
    while (!exit) {
        Task t = getTask();
        t();
    }
}