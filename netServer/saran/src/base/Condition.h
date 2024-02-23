#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "base/Mutex.h"
#include "base/NonCopyable.h"

namespace saran {

namespace base {

class Condition : NonCopyable {
public:
    explicit Condition(Mutex& mutex) : mutex_(mutex) { 
        pthread_cond_init(&condition_, nullptr);
    }

    ~Condition() {
        pthread_cond_destroy(&condition_);
    }

    void wait() {
        pthread_cond_wait(&condition_, mutex_.getMutex());    
    }

    bool waitForSeconds(double seconds);

    void notify() {
        pthread_cond_signal(&condition_);        
    }

    void notifyAll() {
        pthread_cond_broadcast(&condition_);
    }

private:
    Mutex &mutex_;
    pthread_cond_t condition_;
};

}

}

#endif