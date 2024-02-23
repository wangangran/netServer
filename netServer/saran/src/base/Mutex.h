#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>
#include "base/NonCopyable.h"

namespace saran {

namespace base {

template<typename T>
class LockGuard {
public:
    explicit LockGuard(T *mutex) : mutex_(mutex){
        if (nullptr != mutex_) {
            mutex_->lock();
        }
    }

    ~LockGuard() {
        if (nullptr != mutex_) {
            mutex_->unlock();
        }
    }

private:
    T *mutex_ = nullptr;
};

class Mutex : NonCopyable {
public:
    explicit Mutex() {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mutex);
    }

    void lock() {
        pthread_mutex_lock(&mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t *getMutex() {
        return &mutex;
    }

private:
    pthread_mutex_t mutex;
};

}

}
#endif