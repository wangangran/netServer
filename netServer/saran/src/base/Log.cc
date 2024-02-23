#include "Log.h"

using namespace saran::base;

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char *file, uint32_t line, uint32_t threadId, uint64_t time) :
    logger_(logger),
    level_(level),
    file_(file),
    line_(line),
    threadId_(threadId),
    time_(time)
{
    stream_ << file << line << threadId << time << " "; 
}

LogEvent::~LogEvent() {
    logger_->log(std::move(getContent()));
}


Logger::Logger(LogAppenderBase::ptr append, const std::string &name) :
    name_(name),
    appender_(append)
{

}

// void Logger::log(LogEvent::ptr event)
// {

// }

void Logger::log(std::string &&str)
{
    appender_->append(str.c_str(), str.size());
}