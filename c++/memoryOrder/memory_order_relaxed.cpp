//
// Created by Administrator on 2024-04-11.
//

#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> g_x;
std::atomic<bool> g_y;
std::atomic<int> g_z;

void write_x_then_y() {
    g_y.load(std::memory_order_relaxed);
    g_x.store(true, std::memory_order_relaxed);                 // 1
    g_y.store(true, std::memory_order_relaxed);                 // 2
}

void read_x_then_y() {
    while (!g_y.load(std::memory_order_relaxed));               // 3
    if (g_x.load(std::memory_order_relaxed)) {                  // 4
        ++g_z;
    }
}

int main(int argc, char *argv[]) {
    int count = 10000;
    while (count > 0) {
        g_z = 0;
        g_x = false;
        g_y = false;
        std::thread writeTr(write_x_then_y);
        std::thread readTr(read_x_then_y);
        writeTr.join();
        readTr.join();
        // 断言可能会报错，因为1,2指令可能存在重排(x86机器不会测试很多遍不会, arm平台测试了很多次也没问题)
        assert(g_z.load() != 0);
        count--;
    }
    return 0;
}