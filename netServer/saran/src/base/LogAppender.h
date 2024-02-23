#ifndef _LOGAPPENDER_H_
#define _LOGAPPENDER_H_

#include <memory>
#include <vector>
#include <atomic>
#include <string>

#include "base/Mutex.h"
#include "base/Thread.h"
#include "base/Condition.h"

namespace saran {

namespace base {

class LogBuffer;

class LogAppenderBase {
public:
    using ptr = std::shared_ptr<LogAppenderBase>;

    virtual ~LogAppenderBase() {}
    virtual void append(const char *msg, size_t len) = 0;
};

class AsyncFileAppender : public LogAppenderBase {
public:
    explicit AsyncFileAppender(const std::string &basename);
    ~AsyncFileAppender();
    
    void append(const char *msg, size_t len);
    void start();
    void stop();
private:
    void threadFunc();
private:
    const std::string   baseName_;    
    std::atomic<bool>   started_;
    std::atomic<bool>   running_;
    Mutex               mutex_;
    Condition           condition_;
    double              waitSeconds_;
    Thread              flushThread_;    
    std::unique_ptr<LogBuffer> curBuffer_;
    std::vector<std::unique_ptr<LogBuffer>> buffers_;
};

}

}

#endif