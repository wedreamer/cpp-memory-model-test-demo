#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <iostream>

// 停止标记
// static 不会导致该问题
// static bool isStop = false;

// 不会导致永远的循环 -> 还在学习中, java 会导致
TEST(memory, visible)
{
    // 停止标记
    // static 不会导致该问题
    // static bool isStop = false;
    bool isStop = false;
    auto func = [&]
    {
        auto foo = [&]
        {
            while (true)
            {
                bool b = isStop;
                ASSERT_TRUE(b);
                if (b) {
                    isStop = false;
                    break;
                }
            }
        };

        auto thr = std::thread([&]
                               {
                            // 睡 1 s
                            std::this_thread::sleep_for(std::chrono::microseconds(1));
                            // 停止 foo 的循环
                            isStop = true; });
        thr.join();
        foo();
    };

    for (size_t i = 0; i < 1000; i++)
    {
        func();
    }
}
