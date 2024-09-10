#ifndef _TCPCONNECT_H_
#define _TCPCONNECT_H_

#include "net/Channel.h"

namespace saran {

namespace net {

class TcpConnect {
public:
    explicit TcpConnect(std::shared_ptr<Epoll> poll, int fd);
    ~TcpConnect();
    
    void handleRead();
    void handleWrite();
private:
    std::weak_ptr<Epoll> epollWeakPtr_;
    int fd_;
    Channel connectChl_;
};

}

}


#endif