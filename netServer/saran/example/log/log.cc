#include "base/Log.h"

using namespace saran::base;

int main(int argc, char *argv[]) {
    Logger::ptr log(new Logger(LogAppenderBase::ptr(new AsyncFileAppender("./logFile"))));
    for (int i = 0; i < /*10000000*/1; ++i) {
        LogD(log) << "hello world";
    }
    return 0;
}