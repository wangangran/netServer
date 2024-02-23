#include "Accept.h"
#include "net/Epoll.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

using namespace saran::net;

Accept::Accept(std::shared_ptr<Epoll> loop, const HostAddr &addr) :
   epollWeakPtr_(loop),
   sock_(addr),
   acceptChannel_(loop, sock_.getfd()),
   idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
   sock_.setReuseAddr(true);
   sock_.setReusePort(true);
   sock_.bind();
   sock_.listen();
   acceptChannel_.setReadCallback(std::bind(&Accept::handleRead, this));  
   acceptChannel_.enableReadEvent();
}

void Accept::handleRead()
{
   int clientfd = sock_.accept();
   if (clientfd >= 0) {
      if (newConnetCb_) newConnetCb_(clientfd);
   } else {
      if (errno == EMFILE) {
         ::close(idleFd_);
         idleFd_ = ::accept(sock_.getfd(), NULL, NULL);
         ::close(idleFd_);
         idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
      }
   }
}