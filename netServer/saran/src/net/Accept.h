#ifndef _ACCEPT_H_
#define _ACCEPT_H_

#include "net/Socket.h"
#include "net/Channel.h"

namespace saran {

namespace net {

class Epoll;

class Accept {
public:
    explicit Accept(std::shared_ptr<Epoll> loop, const HostAddr &addr);
    ~Accept() {};

    void setNewConnectCb(NewConnectCallback cb) { newConnetCb_ = cb;}

    void handleRead();

private:
    std::weak_ptr<Epoll> epollWeakPtr_;
    Socket sock_;
    Channel acceptChannel_;
    NewConnectCallback newConnetCb_;
    int idleFd_;
};

}

}

#endif