#include "net/Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

using namespace saran::net;

Socket::Socket(const HostAddr &addr) : 
    addr_(addr)
{
    createSocket();
}

Socket::~Socket()
{
    ::close(fd_);
    std::cout << "socket::~socket" << std::endl;
}

int Socket::createSocket()
{
    fd_ = ::socket(addr_.getFamily(), SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (fd_ < 0) {
        std::cout << "createSocket failed" << std::endl;
    }
    return fd_;
}

int Socket::bind()
{
    if (::bind(fd_, (const struct sockaddr *)&addr_, sizeof(sockaddr)) < 0) {
        std::cout << "bind failed" << std::endl;
        return -1;
    }
    std::cout << "bind success" << std::endl;
    return 0;
}

int Socket::listen()
{
    if (-1 == ::listen(fd_, 128)) {
        std::cout << "listen failed" << std::endl;
        return -1;
    }
    std::cout << "listen success" << std::endl;
    return 0;
}

int Socket::accept()
{
    sockaddr clientaddr;
    socklen_t clientlen = static_cast<socklen_t>(sizeof(clientaddr));
    
    int clientfd = ::accept4(fd_, &clientaddr, &clientlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (-1 == clientfd) {
        std::cout << "accept4 failed" << std::endl;
        return -1;
    }
    std::cout << "accept4 sucess fd" << clientfd <<std::endl;
    return clientfd;
}

void Socket::setReuseAddr(bool on)
{
    int opt = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, static_cast<socklen_t>(sizeof(opt)));
}

void Socket::setReusePort(bool on) 
{
    int opt = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &opt, static_cast<socklen_t>(sizeof(opt)));
}