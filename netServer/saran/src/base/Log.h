#ifndef _LOG_H_
#define _LOG_H_

#include <map>
#include <vector>
#include <memory>
#include <sstream>

#include "base/LogConfig.h"
#include "base/LogAppender.h"
#include "base/NonCopyable.h"
#include "base/Singleton.h"


namespace saran {

namespace base {

class Logger;

static LogConfig gLogConfig;

class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;
    explicit LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char *file, uint32_t line, uint32_t threadId, uint64_t time);
    ~LogEvent();

    const char *getFile() const { return file_; }

    uint32_t getLine() const { return line_; }

    uint32_t getThreadId() const { return threadId_; }

    uint64_t getTime() const { return time_; }

    std::stringstream& getSS() { return stream_;}

    std::string getContent() const { return stream_.str(); }

private:
    std::shared_ptr<Logger>         logger_;
    LogLevel::Level                 level_;
    const char                      *file_ = nullptr;
    uint32_t                        line_ = 0;
    uint32_t                        threadId_ = 0;
    uint64_t                        time_ = 0;
    std::stringstream               stream_;
};

// class LogFormatter {
// public:
//     using ptr = std::shared_ptr<LogFormatter>;

//     class FormatItem {
//     public:
//         using ptr = std::shared_ptr<FormatItem>;
//          virtual ~FormatItem () {}

//          virtual void format(std::ostream &os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) = 0;
//     };

// public:
//     explicit LogFormatter(const std::string &pattern);

//     void Init();
// private:
//     std::string pattern_;
//     std::vector<FormatItem::ptr> items_;
// };

class Logger {
public:
    using ptr = std::shared_ptr<Logger>;
    explicit Logger(LogAppenderBase::ptr append, const std::string &name = "root");
    
    // void log(LogEvent::ptr event);
    void log(std::string &&str);
    inline LogLevel::Level getLevel () const { return level_; }
private:
    Mutex                   mutex_;
    std::string             name_;
    LogLevel::Level         level_ = LogLevel::DEBUG;
    LogAppenderBase::ptr    appender_;
};

class LoggerManager {
public:
    explicit LoggerManager();

    void Init();

    Logger::ptr getLogger(const std::string &name);
    Logger::ptr getRoot() const { return root_; }
private:
    std::map<std::string, Logger::ptr> loggers_;
    Logger::ptr root_;
};

}

}

#define Log(logger, level) \
        if (logger->getLevel() >= level) \
        saran::base::LogEvent::ptr(new saran::base::LogEvent(logger, level, __FILE__, __LINE__, 0, 0))->getSS()


#define LogD(logger) Log(logger, saran::base::LogLevel::DEBUG)

#endif