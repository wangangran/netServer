#pragma once

namespace saran {

template<typename T>
class Comparator {
public:
    virtual ~Comparator();
    
    // if lhs < rhs ==> ret < 0
    // lhs = rhs ==> ret = 0
    // lhs > rhs ==> ret > 0 
    virtual int compare(const T &lhs, const T &rhs) = 0;
};

}