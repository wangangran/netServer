//
// Created by Administrator on 2024/2/26.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RBTree.h"

namespace saran {

class student {
public:
    virtual ~student() = default;

    virtual int getAge() const = 0;
    virtual std::string getHobby(const std::string &) = 0;
};

class MockStudent : public student {
public:
    MOCK_CONST_METHOD0(getAge, int());
    MOCK_METHOD1(getHobby, std::string(const std::string&));
};

TEST(RBTree, Insert) {
    RBTree<std::string, std::string> tree;
    ASSERT_TRUE(tree.insert("name2", "war"));
}

TEST(RBTree, Student) {
    MockStudent s;
    EXPECT_CALL(s, getAge())
        .Times(2)
        .WillOnce(testing::Return(18))
        .WillOnce(testing::Return(20));

    EXPECT_CALL(s, getHobby(testing::_))
        .Times(2)
        .WillOnce(testing::Return("games"))
        .WillOnce(testing::Return("basketball"));

    EXPECT_EQ(s.getAge(), 18);
    EXPECT_EQ(s.getAge(), 20);
    EXPECT_EQ(s.getHobby("best"), "games");
    EXPECT_EQ(s.getHobby("other"), "pingpong");
}

};