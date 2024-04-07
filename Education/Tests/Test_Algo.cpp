#include "Test_Algo.h"

#include "../Algo/Algo.h"


void Test_Algo::BubbleSortTest()
{
    cout << "Bubble test (VecSize -> 0)!" << endl;
    
    const int VecSize = 20000;
    vector<int> Vec;

    for (int i = VecSize; i != 0; i--)
    {
        Vec.push_back(i);
    }

    BubbleTest(Vec);
    BubbleAdaptiveTest(Vec);
    
    cout << "Bubble test (VecSize / 2 -> 0 -> VecSize -> VecSize / 2)!" << endl;
    
    vector<int> VecHalf;
    int n = VecSize / 2;
    for (int i = VecSize; i != 0; i--)
    {
        VecHalf.push_back(n--);

        if (n == 0)
        {
            n = VecSize;
        }
    }
    
    BubbleTest(VecHalf);
    BubbleAdaptiveTest(VecHalf);
}

void Test_Algo::BubbleTest(vector<int> InVector)
{
    cout << "Bubble test started!" << endl;
    
    StartTimer();
    
    Algo::BubbleSort(InVector);

    cout << "Elapsed bubble sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
}

void Test_Algo::BubbleAdaptiveTest(vector<int> InVector)
{
    cout << "Adaptive bubble test started!" << endl;
    
    StartTimer();
    
    Algo::BubbleSortAdaptive(InVector);

    cout << "Elapsed adaptive bubble sort time: " << StopAndReturnElapsedTime() << endl;

    cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
}
