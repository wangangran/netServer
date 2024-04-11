//
// Created by Administrator on 2024-04-11.
//
#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> g_x;
int g_z[10];

void reset() {
    g_z[0] = -1;
    g_z[1] = -1;
    g_z[2] = -1;
    g_z[3] = -1;
    g_z[4] = -1;
    g_z[5] = -1;
    g_z[6] = -1;
    g_z[7] = -1;
    g_z[8] = -1;
    g_z[9] = -1;
    // std::memory_order_release, 在此之前的所有写操作不能重排到g_x.store(false, std::memory_order_release);之后
    g_x.store(false, std::memory_order_release);
}

void write_x_then_y() {
    g_z[0] = 0;
    g_z[1] = 1;
    g_z[2] = 2;
    g_z[3] = 3;
    g_z[4] = 4;
    g_z[5] = 5;
    g_z[6] = 6;
    g_z[7] = 7;
    g_z[8] = 8;
    g_z[9] = 9;
    // std::memory_order_release, 在此之前的所有写操作不能重排到g_x.store(false, std::memory_order_release);之后
    g_x.store(true, std::memory_order_release);
}

void read_x_then_y() {
    // std::memory_order_acquire, 在语句后面的所有读操作，都不能重排到g_x.load(std::memory_order_acquire)之前
    while (!g_x.load(std::memory_order_acquire));

    assert(g_z[0] == 0);
    assert(g_z[1] == 1);
    assert(g_z[2] == 2);
    assert(g_z[3] == 3);
    assert(g_z[4] == 4);
    assert(g_z[5] == 5);
    assert(g_z[6] == 6);
    assert(g_z[7] == 7);
    assert(g_z[8] == 8);
    assert(g_z[9] == 9);
}

int main(int argc, char *argv[]) {
    int count = 10000;
    while (count > 0) {
        reset();
        std::thread writeTr(write_x_then_y);
        std::thread readTr(read_x_then_y);
        writeTr.join();
        readTr.join();
        count--;
    }
    return 0;
}