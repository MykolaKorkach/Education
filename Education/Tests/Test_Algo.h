#pragma once
#include "TestBase.h"

class Test_Algo : public TestBase
{
public:

    void BubbleSortTest();
    void InsertionSortTest();
    void CountingSortTest();
    void QuickSortTest();

private:
    
    template<typename T>
    void BubbleTest(vector<T> InVector);
    template<typename T>
    void BubbleAdaptiveTest(vector<T> InVector);
    
    template<typename T>
    void InsertionTest(vector<T> InVector);
    
    template<typename T>
    void CountingTest(vector<T> InVector);
    template<typename T>
    void CountingStableTest(vector<T> InVector);
    
    template<typename T>
    void QuickLomutoTest(vector<T> InVector);
    template<typename T>
    void QuickHoareTest(vector<T> InVector);
};
