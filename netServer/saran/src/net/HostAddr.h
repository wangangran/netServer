#ifndef _HOSTADDR_H_
#define _HOSTADDR_H_

#include <string>
#include "netinet/in.h"

namespace saran {

namespace net {

class HostAddr {
public:
    explicit HostAddr(const std::string &ip, uint16_t port, bool ipv6 = false);
    explicit HostAddr(uint16_t port, bool ipv6 = false);

    sa_family_t getFamily() { return addr_.sin_family; }   
    sockaddr_in getSockaddr() { return addr_; }
private: 
    union
    {
        struct sockaddr_in      addr_;
        struct sockaddr_in6     addrIn6_;
    };
};

}

}
#endif