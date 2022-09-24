#include <thread>
#include <chrono>
#include <iostream>

// 停止标记
// static 不会导致该问题
// 本现象的原因是编译器优化造成的，线程函数threadFun2中由于频繁的访问a，a的值用的是本线程缓存的值，因此不能看到主存中a的新值。测试下面两种方法有效 
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
