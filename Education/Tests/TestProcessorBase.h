#pragma once

#include <chrono>
#include <iostream>
#include <vector>

struct TestBase;
using std::vector;
using std::cout;
using std::endl;
using std::string;


class TestProcessorBase
{
    
public:

    static TestProcessorBase* Get();

    void RunTests();    
        
        
    ~TestProcessorBase();

protected:
    
    void StartTimer();
    double StopAndReturnElapsedTime() const;
    
private:
    
    TestProcessorBase();
    
    static TestProcessorBase* TestProcessor;

    vector<TestBase*> Tests;
    
    std::chrono::time_point<std::chrono::steady_clock> StartTime;
};
 


