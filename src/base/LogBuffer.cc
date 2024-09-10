#include "LogBuffer.h"
#include <string.h>

using namespace saran::base;

LogBuffer::LogBuffer(size_t total) :
    data_(new char[total]),
    total_(total),
    available_(total),
    cur_(0)
{
    setCookie(cookieStart);
}

LogBuffer::~LogBuffer()
{
    delete[] data_;
    setCookie(cookieEnd);
}

void LogBuffer::clear()
{
    cur_ = 0;
    available_ = total_;
}

void LogBuffer::append(const char *data, size_t len)
{
    if (len <= available_) {
        ::memcpy(data_ + cur_, data, len);
        cur_ += len;
        available_ -= len;
    }
}

const char *LogBuffer::data() const
{
    return data_;
}

size_t LogBuffer::length() const
{
    return cur_;
}

size_t LogBuffer::available() const
{
    return available_;
}

void LogBuffer::cookieStart()
{

}

void LogBuffer::cookieEnd()
{
    
}