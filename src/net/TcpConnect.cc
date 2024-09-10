#include "TcpConnect.h"

using namespace saran::net;

TcpConnect::TcpConnect(std::shared_ptr<Epoll> poll, int fd) :
    epollWeakPtr_(poll),
    fd_(fd),
    connectChl_(poll, fd)
{
    connectChl_.setReadCallback(std::bind(&TcpConnect::handleRead, this));
    connectChl_.setWriteCallback(std::bind(&TcpConnect::handleWrite, this));
    connectChl_.enableReadEvent();
}

TcpConnect::~TcpConnect()
{

}

void TcpConnect::handleRead()
{

}

void TcpConnect::handleWrite()
{

}
