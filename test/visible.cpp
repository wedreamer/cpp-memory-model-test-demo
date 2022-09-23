#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// 永远的循环
TEST(memory, visible)
{
    // 停止标记
    bool isStop = false;
    auto func = [&]
    {
        auto foo = [=]
        {
            while (true)
            {
                bool b = isStop;
                if (b)
                    break;
            }
        };

        auto thr = std::thread([&]
                               {
                            // 睡 5 s 
                            std::this_thread::sleep_for(std::chrono::microseconds(1));
                            // 停止 foo 的循环
                            isStop = true; });
        thr.join();
        foo();
        isStop = false;
    };

    for (size_t i = 0; i < 10000; i++)
    {
        func();
    }
}
