#include "Epoll.h"
#include <string.h>
#include <iostream>
#include <net/Channel.h>

using namespace saran::net;


Epoll::Epoll() : 
    epfd_(epoll_create(1))
{

}

Epoll::~Epoll()
{

}

void Epoll::poll()
{
    while (true) {
        int nready = epoll_wait(epfd_, events_, MAX_EPOLL_SIZE, 10000);
        for (int i = 0; i < nready; ++i) {
            Channel* chl = static_cast<Channel*>(events_[i].data.ptr);
            chl->handleEvent();
        }
    }
}

int Epoll::updateChannel(Channel *ch)
{
    if (nullptr == ch) {
        return -1;
    }

    epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = ch->getEvent();
    ev.data.ptr = static_cast<Channel*>(ch);
    
    if (channels_.find(ch->getFd()) != channels_.end()) {
        if (epoll_ctl(epfd_, EPOLL_CTL_MOD, ch->getFd(), &ev) < 0){
            return -1;
        }
        channels_[ch->getFd()] = ch;        
    } else {
        if (epoll_ctl(epfd_, EPOLL_CTL_ADD, ch->getFd(), &ev) < 0) {
            return -1;
        }
        std::cout << "updateChannel" << std::endl;
        channels_[ch->getFd()] = ch;    
    }
    return 0;
}

int Epoll::removeChannel(int fd)
{
    if (channels_.find(fd) != channels_.end()) {
        if (epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, nullptr) < 0) {
            std::cout << "removeChannel error" << std::endl;        
            return -1;
        }
        channels_.erase(fd);
    }   
    return 0;
}