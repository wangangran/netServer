#ifndef _EPOLL_H_
#define _EPOLL_H_

#include <sys/epoll.h>
#include <map>
#include <vector>

namespace saran {

namespace net {

class Channel;

class Epoll {
    static const int MAX_EPOLL_SIZE = 1024;
public:
    explicit Epoll();
    ~Epoll();

    void poll();

    int updateChannel(Channel *arg);
    int removeChannel(int fd);
private:
    using ChannelMap = std::map<int, Channel*>;
    using EventList = std::vector<struct epoll_event>;
    int epfd_ = 0;
    ChannelMap channels_;
    struct epoll_event events_[MAX_EPOLL_SIZE];
};

}

}
#endif
