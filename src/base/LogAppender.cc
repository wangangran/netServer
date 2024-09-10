#include "LogAppender.h"
#include "base/Log.h"
#include "base/LogBuffer.h"
#include "base/LogFile.h"

#include <sys/stat.h>

using namespace saran::base;

AsyncFileAppender::AsyncFileAppender(const std::string &basename) :
    baseName_(basename),
    started_(false),
    running_(false),
    condition_(mutex_),
    waitSeconds_(gLogConfig.fileOption.logFlushInterval),
    flushThread_(std::bind(&AsyncFileAppender::threadFunc, this), nullptr),
    curBuffer_(new LogBuffer(gLogConfig.logBufferSize))
{
    mkdir(baseName_.c_str(), 0755);
    start();
}

AsyncFileAppender::~AsyncFileAppender()
{
    if (running_) {
        stop();
    }
}

void AsyncFileAppender::append(const char *msg, size_t len)
{
    LockGuard<Mutex> mutexlock(&mutex_);
    if (curBuffer_->available() > len) {
        curBuffer_->append(msg, len);
    } else {
        if (buffers_.size() > gLogConfig.logBufferSize) {
            condition_.notify();
            return;
        }
        buffers_.push_back(std::move(curBuffer_));
        curBuffer_.reset(new LogBuffer(gLogConfig.logBufferSize));
        curBuffer_->append(msg, len);

        condition_.notify();
    }
}

void AsyncFileAppender::start()
{
    started_ = true;
    running_ = true;
    flushThread_.start();
}

void AsyncFileAppender::stop()
{
    started_ = false;
    condition_.notify();
    flushThread_.join();
}

void AsyncFileAppender::threadFunc()
{
    std::unique_ptr<LogBuffer> buffer(new LogBuffer(gLogConfig.logBufferSize));
    std::vector<std::unique_ptr<LogBuffer>> logBuffers;
    logBuffers.reserve(gLogConfig.logBufferNum);

    LogFile logFile(baseName_,  gLogConfig.fileOption.logFlushFileSize,
                    gLogConfig.fileOption.logFlushInterval, 1024,
                    gLogConfig.fileOption.fileWriteType);

    while (running_) {
        {
        LockGuard<Mutex> mutexlock(&mutex_);
        if (buffers_.empty()) {
            condition_.waitForSeconds(waitSeconds_);        
        }

        if (buffers_.empty() && curBuffer_->length() == 0) {
            continue;
        }

        buffers_.push_back(std::move(curBuffer_));

        logBuffers.swap(buffers_);
        curBuffer_ = std::move(buffer);
        curBuffer_->clear();
        }

        for (const auto &buf : logBuffers) {
            logFile.append(buf->data(), buf->length());
        }

        buffer = std::move(logBuffers[0]);
        buffer->clear();
        logBuffers.clear();

        logFile.flush();

        if (!started_) {
            LockGuard<Mutex> mutexlock(&mutex_);
            if (curBuffer_->length() == 0) {
                running_ = false;
            }
        }
    }

    logFile.flush();
}