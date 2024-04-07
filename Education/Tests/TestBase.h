#pragma once

#include <chrono>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

class TestBase
{
    
public:

    void StartTimer();
    double StopAndReturnElapsedTime() const;
        
    template<typename T>
    void PrintVector(const vector<T>& InVector);
        
    template<typename T>
    bool IsVectorSorted(const vector<T>& InVector);

private:
    
    std::chrono::time_point<std::chrono::steady_clock> StartTime;
};
 

template <typename T>
void TestBase::PrintVector(const vector<T>& InVector)
{
    for (const T& i : InVector)
    {        
        cout << i << " "; 
    }
    cout << endl;
}

template <typename T>
bool TestBase::IsVectorSorted(const vector<T>& InVector)
{
    bool bSorted = true;

    for (size_t i = 1; i < InVector.size(); i++)
    {
        if (InVector[i] < InVector[i - 1])
        {
            bSorted = false;
            break;
        }
    }
    return bSorted;
}
