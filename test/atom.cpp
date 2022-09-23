#include <gtest/gtest.h>
#include <vector>
#include <thread>
#include <iostream>

// 原子性
TEST(memory, atom)
{
    static int balance = 10;
    auto genThreads = [&]
    {
        auto withdraw = new std::thread([&]
                                        { balance -= 5; });
        auto deposit = new std::thread([&]
                                       { balance += 5; });
        auto threads = std::vector<std::thread *>{};
        threads.push_back(deposit);
        threads.push_back(withdraw);
        // balance -> 5 || 10 || 15
        for (auto &thr : threads)
            thr->join();
        EXPECT_TRUE(balance == 5 || balance == 10 || balance == 15)
            << "balance: \t" << ::testing::PrintToString(balance) << std::endl;
        balance = 10;
    };
    for (size_t i = 0; i < 1000; i++)
    {
        genThreads();
    }
}
