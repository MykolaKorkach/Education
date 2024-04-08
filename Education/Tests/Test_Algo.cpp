#include "Test_Algo.h"

#include "../Algo/Algo.h"

static int VectorSize = 10000;

struct TestStruct
{
    TestStruct()
    {
        I = rand() % 50;
        D = static_cast<double>(rand() % 40);
        F = static_cast<float>(rand() % 30);
    }

    bool operator>(const TestStruct& Other) const
    {
        return I > Other.I;
    }

    bool operator<(const TestStruct& Other) const
    {
        return I < Other.I;
    }
    
    int I;
    float F;
    double D;
};

void Test_Algo::BubbleSortTest()
{
    cout << "Bubble test (VecSize -> 0)!" << endl;
    
    vector<int> Vec;

    for (int i = VectorSize; i != 0; i--)
    {
        Vec.push_back(i);
    }

    BubbleTest(Vec);
    BubbleAdaptiveTest(Vec);
    
    cout << "Bubble test (VecSize / 2 -> 0 -> VecSize -> VecSize / 2)!" << endl;
    
    vector<int> VecHalf;
    int n = VectorSize / 2;
    for (int i = VectorSize; i != 0; i--)
    {
        VecHalf.push_back(n--);

        if (n == 0)
        {
            n = VectorSize;
        }
    }
    
    BubbleTest(VecHalf);
    BubbleAdaptiveTest(VecHalf);
}

void Test_Algo::InsertionSortTest()
{    
    vector<int> Vec;

    for (int i = VectorSize; i != 0; i--)
    {
        Vec.push_back(i);
    }

    InsertionTest(Vec);
}

void Test_Algo::CountingSortTest()
{
    vector<TestStruct> Vec;

    for (int i = VectorSize; i != 0; i--)
    {
        Vec.emplace_back();
    }

    CountingTest(Vec);
    CountingStableTest(Vec);
    
    vector<int> VecPairs;

    int P = VectorSize;
    for (int i = VectorSize; i != 0; i--)
    {
        VecPairs.push_back(P);
        if (i % 5)
        {
            P--;
        }
    }

    CountingTest(VecPairs);
    CountingStableTest(VecPairs);
    
    vector<int> VecRand;

    for (int i = VectorSize; i != 0; i--)
    {        
        VecRand.push_back(rand() % 100);
    }

    CountingTest(VecRand);
    CountingStableTest(VecRand);
}




template<typename T>
void Test_Algo::BubbleTest(vector<T> InVector)
{
    cout << "Bubble test started!" << endl;
    
    StartTimer();
    
    Algo::BubbleSort(InVector);

    cout << "Elapsed bubble sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
}


template<typename T>
void Test_Algo::BubbleAdaptiveTest(vector<T> InVector)
{
    cout << "Adaptive bubble test started!" << endl;
    
    StartTimer();
    
    Algo::BubbleSortAdaptive(InVector);

    cout << "Elapsed adaptive bubble sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
}


template<typename T>
void Test_Algo::InsertionTest(vector<T> InVector)
{
    cout << "Insertion sort test started!" << endl;
    
    StartTimer();
    
    Algo::InsertionSort(InVector);

    cout << "Elapsed insertion sort sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
}


template<typename T>
void Test_Algo::CountingTest(vector<T> InVector)
{
    cout << "Counting sort test started!" << endl;
    
    vector<T> SortedVector;
    StartTimer();
    
    Algo::CountingSort(InVector, SortedVector);

    cout << "Elapsed counting sort sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(SortedVector) ? "" : "not ") << "sorted" << endl;
}


template<typename T>
void Test_Algo::CountingStableTest(vector<T> InVector)
{
    cout << "Counting stable sort test started!" << endl;
    
    vector<T> SortedVector;
    StartTimer();
    
    Algo::CountingStableSort(InVector, SortedVector);

    cout << "Elapsed counting stable sort sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(SortedVector) ? "" : "not ") << "sorted" << endl;
}
