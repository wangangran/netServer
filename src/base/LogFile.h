#ifndef _LOGFILE_H_
#define _LOGFILE_H_

#include <string>
#include <memory>
#include "base/LogConfig.h"

namespace saran {

namespace base {

class FileWrite {
public:
    FileWrite() = default;
    virtual ~FileWrite() = default;

    virtual void append(const char *msg, uint32_t len) = 0;
    virtual void flush() = 0;
    virtual uint32_t wirttenBytes() const = 0;
};

class MMapFileWrite : public FileWrite {
public:
    explicit MMapFileWrite(const std::string &basename, uint32_t memsize);
    ~MMapFileWrite();

    void append(const char *msg, uint32_t len) override;
    void flush() override;
    uint32_t wirttenBytes() const override;

private:
    int         fd_  = -1;
    char        *buffer_;
    uint32_t    memSize_;
    uint32_t    writed_ = 0;
};

class AppendFileWrite : public FileWrite {
public:
    explicit AppendFileWrite(const std::string &filename);
    ~AppendFileWrite();

    void append(const char *msg, uint32_t len) override;
    void flush() override;
    uint32_t wirttenBytes() const override;
    
private:
    FILE        *fp_ = nullptr;
    char        buffer_[64 * 1024];
    uint32_t    writed_ = 0;
};

class LogFile {
public:
    explicit LogFile(const std::string &basename, uint32_t rollSize, uint32_t flushInterval,
                     uint32_t checkInterval, FileWriterType fWriteType);
    ~LogFile() {};

    void append(const char *msg, uint32_t len);
    void flush();
    
private:
    bool rollFile();
    std::string getLogFileName(const std::string &basename, time_t *now);
    std::string getHostName();

private:
    std::string     baseName_;
    uint32_t        rollSize_;
    uint32_t        flushInterval_;
    uint32_t        checkFreqCount_;
    uint32_t        count_ = 0;
    time_t          startOfPeriod_ = 0;
    time_t          lastRoll_ = 0;
    time_t          lastFlush_ = 0;    
    FileWriterType  fWriteType_;
    std::shared_ptr<FileWrite> fileWrite_;
    constexpr static int kRollPerSeconds_ = 60 * 60 * 24;
};

}

}

#endif