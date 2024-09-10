#ifndef _LOGBUFFER_H_
#define _LOGBUFFER_H_

#include <sys/types.h>

namespace saran {

namespace base {

class LogBuffer {
public:
    explicit LogBuffer(size_t total = 1024 * 1024 * 10);
    ~LogBuffer();

    void clear();
    void append(const char *data, size_t len);
    const char *data() const;
    size_t length() const;
    size_t available() const;

    void setCookie(void (*cookie) ()) { cookie_ = cookie; }

private:    
    static void cookieStart();
    static void cookieEnd();    

private:
    void (*cookie_)();
    char            *data_;
    const size_t    total_;
    size_t          available_;
    size_t          cur_;
};

}

}

#endif