#include "Condition.h"

#include <errno.h>
#include <stdint.h>

using namespace saran::base;

bool Condition::waitForSeconds(double seconds)
{
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME, &abstime);

    const int64_t nanoSecondPerSecond = 1000000000;
    int64_t nanoseconds = static_cast<int64_t>(seconds * nanoSecondPerSecond);
    
    abstime.tv_sec = static_cast<time_t>((abstime.tv_nsec + nanoseconds) / nanoSecondPerSecond);
    abstime.tv_nsec = static_cast<long>((abstime.tv_nsec + nanoseconds) % nanoSecondPerSecond);

    return ETIMEDOUT == pthread_cond_timedwait(&condition_, mutex_.getMutex(), &abstime);
}