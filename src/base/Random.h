#pragma once

#include <iostream>
#include <random>

namespace saran {

class Random {
public:
    // 该函数实现 1/n 的概率返回true    
    bool oneIn(int n) {
        std::random_device seed;                                // 硬件生成随机数种子
	    std::ranlux48 engine(seed());                           // 利用种子生成随机数引擎
        std::uniform_int_distribution<> distrib(0, n - 1);      // 设置随机数范围，并为均匀分布
        int random = distrib(engine);                           // 随机数
        // std::cout << random << std::endl;
        return (random % n == 0);
    }
};

}