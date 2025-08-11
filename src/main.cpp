#include "../include/Vector.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

struct Timer
{
    std::string message;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<float> duration;
    
    Timer(std::string message): message { message }
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        std::cout << message << ms << " ms" << '\n';
    }
};

class Benchmarks
{
private:
    std::string test_value;

    void std_lib_benchmark()
    {
        Timer T("std::vector implementation took ");
        
        std::vector<std::string> myVec;

        for (size_t i = 0; i < 1000000; i++)
        {
            myVec.push_back(test_value);
        }

    }

    void custom_lib_benchmark()
    {
        Timer T("custom vector implementation took ");
        
        Vector<std::string> myVec;

        for (size_t i = 0; i < 1000000; i++)
        {
            myVec.push_back(test_value);
        }  
    }


public:

Benchmarks(std::string value): 
test_value { value }
{ }



void runTests()
{
    std_lib_benchmark();
    custom_lib_benchmark();
}

};



int main()
{
    std::cout << "=====Executing Benchmark Test in C++=====\n";
    std::cout << "Pushing Back 1,000,000 Test strings\n";
    
    std::string test_value = "This is my test string";

    Benchmarks Tests(test_value);

    Tests.runTests();

}