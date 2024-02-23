#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#define MAX_BUFFER_SIZE 1024

#include <net/CallBackDef.h>
#include <memory>

namespace saran {

namespace net {

class Epoll;

class Channel {
public:
    explicit Channel(std::shared_ptr<Epoll> loop, int fd);
    ~Channel();
    
    void setReadCallback(EventCallback cb) { readcb_ = cb; }
    void setWriteCallback(EventCallback cb) { writecb_ = cb; }
    void setErrorCallback(EventCallback cb) { errorcb_ = cb; }

    void update();
    void handleEvent();
    void enableReadEvent();
    void disableReadEvent();
    void enableWriteEvent();
    void disableWriteEvent();
    void enableAllEvent();
    void disableAllEvent();

    int getEvent() { return event_; }
    int getFd() { return fd_; }
private:
    std::weak_ptr<Epoll> epollWeakPtr_;
    int fd_;
    int event_;
    EventCallback readcb_;
    EventCallback writecb_;
    EventCallback errorcb_;

    unsigned char recvBuf[MAX_BUFFER_SIZE];
    unsigned char sendBuf[MAX_BUFFER_SIZE];
};

}

}

#endif