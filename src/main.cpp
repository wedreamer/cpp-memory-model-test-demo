#include <vector>
#include <thread>
#include <iostream>

struct Restult
{
    int r1; // Member (int variable)
    int r2;
};

int main()
{
    int a = 0;
    int b = 0;
    auto r = Restult{0, 0};
    auto genThreads = [&]
    {
        auto t1 = new std::thread([&]
                                  { b = 1; r.r2 = a; });
        auto t2 = new std::thread([&]
                                  { b = 1; r.r2 = a; });
        auto threads = std::vector<std::thread *>{};
        threads.push_back(t1);
        threads.push_back(t2);
        for (auto &thr : threads)
            thr->join();
        std::cout << "r.r1 : \t" << r.r1 << std::endl;
        std::cout << "r.r2 : \t" << r.r2 << std::endl;
    };
    for (size_t i = 0; i < 2; i++)
    {
        genThreads();
    }
    return 0;
}
