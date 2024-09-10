#ifndef _LOGCONFIG_H_
#define _LOGCONFIG_H_

#include <string>

namespace saran {

namespace base {

class LogLevel {
public:
    enum Level {
        FATAL = 0,
        ERROR = 1,
        WARN = 2,
        INFO = 3,
        DEBUG = 4,
        TRACE = 5,
    };
};

typedef enum 
{   
    MMAPFILE = 0, 
    APPENDFILE 
} FileWriterType;
    
struct FileOption {
    std::string     filePath;
    uint32_t        logFlushFileSize;
    double          logFlushInterval;
    FileWriterType  fileWriteType = APPENDFILE;
};

struct LogConfig {
    uint32_t        logBufferSize = 4000;
    uint32_t        logBufferNum = 2;
    LogLevel::Level logLevel = LogLevel::Level::INFO;
    FileOption      fileOption;        
};

}

}


#endif