#include "Channel.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <net/Epoll.h>

using namespace saran::net;

static const int EPOLLNONEVENT = 0;

Channel::Channel(std::shared_ptr<Epoll> loop, int fd) :
    epollWeakPtr_(loop),
    fd_(fd),
    event_(EPOLLNONEVENT)
{

}

Channel::~Channel()
{

}

void Channel::update()
{
    std::shared_ptr<Epoll> ep = epollWeakPtr_.lock();
    if (ep) {
        ep->updateChannel(this);
    }
}

void Channel::handleEvent()
{
    if ((event_ & EPOLLHUP) && !(event_ & EPOLLIN)) {
        //register epollin epollout event
    }

    if (event_ & EPOLLERR) {
        if (errorcb_) errorcb_();     
    }

    if (event_ & EPOLLIN) {
       if (readcb_) readcb_();
    }
    
    if (event_ & EPOLLOUT) {
        if (writecb_) writecb_();
    }
}

void Channel::enableReadEvent()
{
    event_ |= EPOLLIN;
    update();
}

void Channel::disableReadEvent()
{
    event_ &= ~EPOLLIN;
    update();
}

void Channel::enableWriteEvent()
{
    event_ |= EPOLLOUT;    
    update();
}

void Channel::disableWriteEvent()
{
    event_ &= ~EPOLLOUT;
    update();
}

void Channel::enableAllEvent()
{
    event_ |= EPOLLIN;
    event_ |= EPOLLOUT;
    update();
}

void Channel::disableAllEvent()
{
    event_ = EPOLLNONEVENT;
    update();
}