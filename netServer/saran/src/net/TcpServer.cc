#include "TcpServer.h"
#include "net/Accept.h"
#include "net/Epoll.h"
#include "net/TcpConnect.h"
#include <assert.h>
#include <iostream>

using namespace saran::net;

TcpServer::TcpServer(const HostAddr &addr) :
    poll_(new Epoll()),
    accpetPtr_(new Accept(poll_, addr))
{
    assert(accpetPtr_);
    accpetPtr_->setNewConnectCb(std::bind(&TcpServer::onNewConnect, this, std::placeholders::_1));
}

TcpServer::~TcpServer()
{

}

void TcpServer::startLoop()
{
    poll_->poll();
}

void TcpServer::onNewConnect(int fd)
{
    assert(fd > 0);
    std::cout << "onNewConnect fd[fd]" << fd << std::endl;
    TcpConnectPtr conn(new TcpConnect(poll_, fd));
    if (conn) {
        connMap_[fd] = conn;
    }
}