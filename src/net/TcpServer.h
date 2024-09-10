#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include <base/NonCopyable.h>
#include <net/HostAddr.h>
#include <memory>
#include <map>

namespace saran {

namespace net {

class Accept;
class Epoll;
class TcpConnect;

class TcpServer : public base::NonCopyable {
public:
    explicit TcpServer(const HostAddr &addr);
    ~TcpServer();

    void startLoop();
    void onNewConnect(int fd);
private:
    using TcpConnectPtr = std::shared_ptr<TcpConnect>;
    using ConnectMap = std::map<int, TcpConnectPtr>;
  
    std::shared_ptr<Epoll>  poll_;
    std::shared_ptr<Accept> accpetPtr_;
    ConnectMap  connMap_;
};

}

}


#endif