#include <thread>
#include <chrono>

// 停止标记
// static 不会导致该问题
static bool isStop = false;

static void foo()
{
    while (true)
    {
        bool b = isStop;
        if (b)
            break;
    }
}

int main()
{
    auto func = [&]
    {
        auto thr = std::thread([&]
                               {
                            // 睡 5 s 
                            std::this_thread::sleep_for(std::chrono::seconds(10));
                            // 停止 foo 的循环
                            isStop = true; });
        thr.join();
        foo();
    };

    for (size_t i = 0; i < 1; i++)
    {
        func();
    }
}
