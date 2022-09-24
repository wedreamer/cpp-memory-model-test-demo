#include <thread>
#include <chrono>
#include <iostream>

// 停止标记
// static 不会导致该问题
static bool isStop = false;

static void foo()
{
    while (true)
    {
        bool b = isStop;
        if (b)
        {
            if (!isStop)
            {
                std::cout << "isStop : \t"
                          << "false" << std::endl;
            }
            isStop = false;
            break;
        }
    }
}

static void func()
{
    auto thr = std::thread([&]
                           {
                            // 睡 1 ms 
                            std::this_thread::sleep_for(std::chrono::microseconds(1));
                            // 停止 foo 的循环
                            isStop = true; });
    thr.join();
    foo();
}

int main()
{
    for (size_t i = 0; i < 10000; i++)
    {
        func();
    }
}
