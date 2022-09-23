#include <gtest/gtest.h>
#include <thread>
#include <chrono>

// 不会导致永远的循环
TEST(memory, visible)
{
    // 停止标记
    // static 不会导致该问题
    static bool isStop = false;
    auto func = [&]
    {
        auto foo = [&]
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
                            // 睡 1 s 
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            // 停止 foo 的循环
                            isStop = true; });
        thr.join();
        foo();
    };

    for (size_t i = 0; i < 10; i++)
    {
        func();
    }
}
