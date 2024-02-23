#include <gtest/gtest.h>

#include "SkipList.h"

using namespace saran;

class IntComparator {
public:
    int operator() (const int &lhs, const int &rhs) const {
        if (lhs < rhs) return -1;
        if (lhs == rhs) return 0;
        if (lhs > rhs) return 1;

        return 0;
    }
};

int main(int argc, char **argv) {
    IntComparator cmp;
    SkipList<int, IntComparator> sList(cmp);
    for (int i = i; i <= 10000; ++i) {
       sList.push(i); 
    }
    sList.traverse(10);
    return 0;
}
