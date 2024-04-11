#pragma once
#include <map>

#include "TestBase.h"


struct TestStruct
{
    explicit TestStruct(int Val) : Main(Val)
    {
        Second = rand() % 30;
    }

    bool operator>(const TestStruct& Other) const
    {
        return Main > Other.Main;
    }

    bool operator<(const TestStruct& Other) const
    {
        return Main < Other.Main;
    }

    bool operator==(const TestStruct& Other) const
    {
        return Main == Other.Main && Second == Other.Second;
    }
    
    int Main;
    int Second;
};

class Test_SortAlgo : public TestBase
{
public:

    Test_SortAlgo();
    virtual ~Test_SortAlgo() override = default;
    
    void DefineTest() override;
    
    template<typename T>
    void PrintVector(const vector<T>& InVector);
    
private:

    template<typename T>
    bool IsVectorSorted(const vector<T>& InVector);

    bool IsVectorSortStable(const vector<TestStruct>& InSortedVector, const vector<TestStruct>& InInitialVector);
    
    vector<int> VectorInt;
    vector<TestStruct> InitialVectorStruct;
    vector<TestStruct> VectorStruct;    
};


template <typename T>
void Test_SortAlgo::PrintVector(const vector<T>& InVector)
{
    for (const T& i : InVector)
    {        
        cout << i << " "; 
    }
    cout << endl;
}

template <typename T>
bool Test_SortAlgo::IsVectorSorted(const vector<T>& InVector)
{
    bool bSorted = true;

    for (size_t i = 1; i < InVector.size(); i++)
    {
        if (InVector[i - 1] > InVector[i])
        {
            bSorted = false;
            break;
        }
    }
    return bSorted;
}
