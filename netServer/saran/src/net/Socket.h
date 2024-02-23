#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "net/HostAddr.h"
#include <memory>

namespace saran {

namespace net {

class Socket {
public:
    explicit Socket(const HostAddr &addr);
    ~Socket();
    
    int createSocket();
    int bind();
    int listen();
    int accept();

    int getfd() { return fd_; }
    void setReuseAddr(bool on);
    void setReusePort(bool on);
private:
    int fd_;
    HostAddr addr_;
};

}

}


#endif