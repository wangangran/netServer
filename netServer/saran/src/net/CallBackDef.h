#ifndef _CALLBACKDEF_H_
#define _CALLBACKDEF_H_

#include <functional>

namespace saran {

namespace net {
    using AcceptHandleRead = std::function<void ()>;
    using EventCallback = std::function<void ()>;
    using NewConnectCallback = std::function<void (int)>;
}

}

#endif