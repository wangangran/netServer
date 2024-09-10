#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <functional>
#include "base/NonCopyable.h"


namespace saran {

namespace base {

class ThreadData {
public:
    using ThreadFun = std::function<void(void)>;
public:
    explicit ThreadData(ThreadFun fun, void *arg = nullptr) : fun_(fun), arg_(arg){}
    ~ThreadData() {};

    ThreadFun getThreadFun() { return fun_; }
    void *getData() { return arg_; }
private:
    ThreadFun fun_;
    void *arg_ = nullptr;
};

class Thread : NonCopyable {
public:
    explicit Thread(ThreadData::ThreadFun fun, void *arg);
    ~Thread();

    int start();
    void join();
private:
    pthread_t threadId_;
    ThreadData thData_;
};

}

}

#endif