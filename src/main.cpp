#include "../include/Vector.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <numeric> // accumulate

struct Timer
{
    std::chrono::high_resolution_clock::time_point start;
    Timer() { start = std::chrono::high_resolution_clock::now(); }
    double elapsed_ms() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};

class Benchmarks
{
private:
    std::string test_value;
    static constexpr size_t N = 1'000'000;
    static constexpr int trials = 5;

    template <typename VecT>
    double run_one(VecT& v)
    {
        v.clear();
        v.reserve(N);
        Timer t;
        for (size_t i = 0; i < N; i++) {
            v.push_back(test_value);
        }
        
        return t.elapsed_ms();
    }

    template <typename VecT>
    double run_emplace(VecT& v)
    {
        v.clear();
        v.reserve(N);
        Timer t;
        for (size_t i = 0; i < N; i++) {
            v.emplace_back(test_value);
        }
        
        return t.elapsed_ms();
    }

public:
    Benchmarks(std::string value): test_value{ std::move(value) } {}

    void runTests()
    {
        {
            std::vector<std::string> myVec;
            double total = 0;
            for (int i = 0; i < trials; i++) {
                total += run_one(myVec);
            }
            std::cout << "std::vector (push back) avg over " << trials << " trials: "
                      << (total / trials) << " ms\n";
        }

        {
            VectorLite<std::string> myVec;
            double total = 0;
            for (int i = 0; i < trials; i++) {
                total += run_one(myVec);
            }
            std::cout << "custom Vector avg over " << trials << " trials: "
                      << (total / trials) << " ms\n";
        }

        {
            {
                std::vector<std::string> myVec;
                double total = 0;
                for (int i = 0; i < trials; i++) {
                    total += run_one(myVec);
                }
                std::cout << "std::vector (emplace_back) avg over " << trials << " trials: "
                          << (total / trials) << " ms\n";
            }
        }
    }
};

int main()
{
    std::cout << "=====Executing Benchmark Test in C++=====\n";
    std::cout << "Pushing Back 1,000,000 Test strings\n";

    Benchmarks Tests("This is my test string");
    Tests.runTests();
}