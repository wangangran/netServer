#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace saran {

namespace base {

class NonCopyable {
public:
    NonCopyable(const NonCopyable &) = delete;
    void operator=(const NonCopyable &) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};

}

}

#endif