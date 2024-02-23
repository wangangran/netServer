#include <net/HostAddr.h>
#include <strings.h>

#include <arpa/inet.h>

using namespace saran;
using namespace net;
using namespace std;

HostAddr::HostAddr(const string &ip, uint16_t port, bool ipv6)
{
    if (ipv6) {
        bzero(&addrIn6_, sizeof(addrIn6_));
        ::inet_pton(AF_INET6, ip.data(), &addrIn6_.sin6_addr);
        addrIn6_.sin6_family = AF_INET6;
        addrIn6_.sin6_port = ::htons(port);
    } else {
        bzero(&addr_, sizeof(addr_));
        ::inet_pton(AF_INET, ip.data(), &addr_.sin_addr);  
        addr_.sin_family = AF_INET;
        addr_.sin_port = ::htons(port);
    }
}

HostAddr::HostAddr(uint16_t port, bool ipv6)
{
    if (ipv6) {
        bzero(&addrIn6_, sizeof(addrIn6_));
        addrIn6_.sin6_addr = in6addr_any;
        addrIn6_.sin6_family = AF_INET6;
        addrIn6_.sin6_port = htons(port);
    } else {
        bzero(&addr_, sizeof(addr_));
        addr_.sin_addr.s_addr = ::htonl(INADDR_ANY); 
        addr_.sin_family = AF_INET;
        addr_.sin_port = ::htons(port);
    }  
}