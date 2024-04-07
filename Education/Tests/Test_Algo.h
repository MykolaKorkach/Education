#pragma once
#include "TestBase.h"

class Test_Algo : public TestBase
{
public:

    void BubbleSortTest();

private:
    
    void BubbleTest(vector<int> InVector);
    void BubbleAdaptiveTest(vector<int> InVector);
};
