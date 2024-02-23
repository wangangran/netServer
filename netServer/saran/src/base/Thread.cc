#include "Thread.h"

using namespace saran::base;

void *threadFun(void *arg)
{
    ThreadData *td = static_cast<ThreadData*>(arg);
    if (nullptr == td) {
        return nullptr;
    }

    ThreadData::ThreadFun fun = td->getThreadFun();
    fun();
    return nullptr;
}

Thread::Thread(ThreadData::ThreadFun fun, void *arg) : 
    thData_(fun, arg)
{

}

Thread::~Thread()
{
}

int Thread::start()
{
    return pthread_create(&threadId_, nullptr, threadFun, (void*)(&thData_));
}

void Thread::join()
{
    pthread_join(threadId_, nullptr);
}

