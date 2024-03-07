//
// Created by Administrator on 2024/2/26.
//

#include "gtest/gtest.h"
#include "RBTree.h"

namespace saran {
TEST(RBTree, Insert) {
    RBTree<std::string, std::string> tree;
    ASSERT_TRUE(tree.insert("name2", "war"));
}
};