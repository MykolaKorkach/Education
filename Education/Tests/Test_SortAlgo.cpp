#include "Test_Algo.h"

#include "../Algo/Algo.h"

static int VectorSize = 1000;

Test_SortAlgo::Test_SortAlgo()
{
    TestName = "Algo test";
    MaxStage = 3;
}

void Test_SortAlgo::DefineTest()
{
    SetBeforeTestFunc([this]()
    {
        switch (CurrentStage)
        {
        case 0:
            AddOutput("VecSize -> 0");
            for (int i = VectorSize; i != 0; i--)
            {
                VectorInt.push_back(i);
                VectorStruct.emplace_back(i);
            }
            break;
        case 1:
            AddOutput("Random vector");
            for (int i = VectorSize; i != 0; i--)
            {
                VectorInt.push_back(rand() % 100);
                VectorStruct.emplace_back(rand() % 100);
            }
            break;
        case 2:
            AddOutput("Paired vector");
            {
                int P = VectorSize;
                for (int i = VectorSize; i != 0; i--)
                {
                    VectorInt.push_back(P);
                    VectorStruct.emplace_back(P);
                    if (i % 5)
                    {
                        P--;
                    }
                }
            }
            break;
        default:
            cout << "Stage" << CurrentStage << "isn`t covered!" << endl;
            break;
        }
        
        InitialVectorStruct = VectorStruct;
    });
    
    AddPerfTest("Bubble sort", [this]()
    {
        AlgoSort::BubbleSort(VectorInt);
    });
    
    AddPerfTest("Adaptive bubble sort", [this]()
    {
        AlgoSort::BubbleSortAdaptive(VectorInt);
    });
    
    AddPerfTest("Insertion sort", [this]()
    {
        AlgoSort::InsertionSort(VectorInt);
    });
    
    AddPerfTest("Counting sort", [this]()
    {
        AlgoSort::CountingSort(VectorInt);
    });
    
    AddPerfTest("Counting stable sort", [this]()
    {
        AlgoSort::CountingStableSort(VectorInt);
    });
    
    AddPerfTestWithResult("Counting stable sort", [this]()
    {
        AlgoSort::CountingStableSort(VectorStruct);
    },[this]()
    {
        IsVectorSortStable(VectorStruct, InitialVectorStruct);
    }
    );
    
    AddPerfTest("Quick Lomuto sort", [this]()
    {
        AlgoSort::QuickLomutoSort(VectorInt);
    });
    
    AddPerfTest("Quick Hoare sort", [this]()
    {
        AlgoSort::QuickHoareSort(VectorInt);
    });
    
    AddPerfTestWithResult("Merge sort", [this]()
    {
        AlgoSort::MergeSort(VectorStruct);
    },[this]()
    {
        IsVectorSortStable(VectorStruct, InitialVectorStruct);
    });


    SetAfterTestFunc([this]()
    {
        const bool bIntSorted = IsVectorSorted(VectorInt);
        const bool bStructSorted = IsVectorSorted(VectorStruct);
        AddOutput("Vector was " + string(bIntSorted || bStructSorted ? "" : "not ") + "sorted!");
        
        VectorInt.clear();
        VectorStruct.clear();
    });
}

bool Test_SortAlgo::IsVectorSortStable(const vector<TestStruct>& InSortedVector, const vector<TestStruct>& InInitialVector)
{
    struct CountStruct
    {
        CountStruct() = default;
        CountStruct(size_t InIndex)
        {
            Indexes.push_back(InIndex);
        }
        size_t GetIndex()
        {
            return Indexes[NextIndex++];
        }
        
        vector<size_t> Indexes;
        size_t NextIndex = 0;
    };
    
    std::map<int, CountStruct> CountMap;

    for (size_t Index = 0; Index < InInitialVector.size(); Index++)
    {
        if (!CountMap.contains(InitialVectorStruct[Index].Main))
        {
            CountMap.emplace(InitialVectorStruct[Index].Main, CountStruct(Index));
        }
        else
        {            
            CountMap[InitialVectorStruct[Index].Main].Indexes.push_back(Index);
        }
    }

    bool bStable = true;
    for (const TestStruct& Struct : InSortedVector)
    {
        CountStruct& Count = CountMap[Struct.Main];

        if (InitialVectorStruct[Count.GetIndex()] == Struct)
        {
            continue;
        }
        bStable = false;
    }

    AddOutput("Vector sort is " + string(bStable ? "" : "NOT ") + "stable!");
    return bStable;
}

// void Test_Algo::BubbleSortTest()
// {
//     cout << "Bubble test (VecSize -> 0)!" << endl;
//     
//     vector<int> Vec;
//
//     for (int i = VectorSize; i != 0; i--)
//     {
//         Vec.push_back(i);
//     }
//
//     BubbleTest(Vec);
//     BubbleAdaptiveTest(Vec);
//     
//     cout << "Bubble test (VecSize / 2 -> 0 -> VecSize -> VecSize / 2)!" << endl;
//     
//     vector<int> VecHalf;
//     int n = VectorSize / 2;
//     for (int i = VectorSize; i != 0; i--)
//     {
//         VecHalf.push_back(n--);
//
//         if (n == 0)
//         {
//             n = VectorSize;
//         }
//     }
//     
//     BubbleTest(VecHalf);
//     BubbleAdaptiveTest(VecHalf);
// }
//
// void Test_Algo::InsertionSortTest()
// {    
//     vector<int> Vec;
//
//     for (int i = VectorSize; i != 0; i--)
//     {
//         Vec.push_back(i);
//     }
//
//     InsertionTest(Vec);
// }
//
// void Test_Algo::CountingSortTest()
// {
//     vector<TestStruct> Vec;
//
//     for (int i = VectorSize; i != 0; i--)
//     {
//         Vec.emplace_back();
//     }
//
//     cout << "Full reverted vector" << endl;
//     CountingTest(Vec);
//     CountingStableTest(Vec);
//     
//     vector<int> VecPairs;
//
//     int P = VectorSize;
//     for (int i = VectorSize; i != 0; i--)
//     {
//         VecPairs.push_back(P);
//         if (i % 5)
//         {
//             P--;
//         }
//     }
//
//     cout << "Full reverted vector %5" << endl;
//     CountingTest(VecPairs);
//     CountingStableTest(VecPairs);
//     
//     vector<int> VecRand;
//
//     for (int i = VectorSize; i != 0; i--)
//     {        
//         VecRand.push_back(rand() % 100);
//     }
//
//     cout << "Random elements %100" << endl;
//     CountingTest(VecRand);
//     CountingStableTest(VecRand);
// }
//
// void Test_Algo::QuickSortTest()
// {
//     vector<int> Vec;
//
//     for (int i = VectorSize; i != 0; i--)
//     {
//         Vec.push_back(i);
//     }
//     
//     QuickLomutoTest(Vec);
//     QuickHoareTest(Vec);
// }

//
// template<typename T>
// void Test_Algo::BubbleTest(vector<T> InVector)
// {
//     cout << "Bubble test started!" << endl;
//     
//     StartTimer();
//     
//     AlgoSort::BubbleSort(InVector);
//
//     cout << "Elapsed bubble sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
// }
//
//
// template<typename T>
// void Test_Algo::BubbleAdaptiveTest(vector<T> InVector)
// {
//     cout << "Adaptive bubble test started!" << endl;
//     
//     StartTimer();
//     
//     AlgoSort::BubbleSortAdaptive(InVector);
//
//     cout << "Elapsed adaptive bubble sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
// }
//
//
// template<typename T>
// void Test_Algo::InsertionTest(vector<T> InVector)
// {
//     cout << "Insertion sort test started!" << endl;
//     
//     StartTimer();
//     
//     AlgoSort::InsertionSort(InVector);
//
//     cout << "Elapsed insertion sort sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
// }
//
//
// template<typename T>
// void Test_Algo::CountingTest(vector<T> InVector)
// {
//     cout << "Counting sort test started!" << endl;
//     
//     vector<T> SortedVector;
//     StartTimer();
//     
//     AlgoSort::CountingSort(InVector, SortedVector);
//
//     cout << "Elapsed counting sort sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(SortedVector) ? "" : "not ") << "sorted" << endl;
// }
//
//
// template<typename T>
// void Test_Algo::CountingStableTest(vector<T> InVector)
// {
//     cout << "Counting stable sort test started!" << endl;
//     
//     vector<T> SortedVector;
//     StartTimer();
//     
//     AlgoSort::CountingStableSort(InVector, SortedVector);
//
//     cout << "Elapsed counting stable sort sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(SortedVector) ? "" : "not ") << "sorted" << endl;
// }
//
// template <typename T>
// void Test_Algo::QuickLomutoTest(vector<T> InVector)
// {
//     cout << "Quick Lomuto sort test started!" << endl;
//     
//     vector<T> SortedVector;
//     StartTimer();
//     
//     AlgoSort::QuickLomutoSort(InVector);
//
//     cout << "Elapsed quick Lomuto sort sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;    
// }
//
// template <typename T>
// void Test_Algo::QuickHoareTest(vector<T> InVector)
// {
//     cout << "Quick Hoare sort test started!" << endl;
//     
//     vector<T> SortedVector;
//     StartTimer();
//     
//     AlgoSort::QuickHoareSort(InVector);
//
//     cout << "Elapsed quick Hoare sort sort time: " << StopAndReturnElapsedTime() << endl;
//
//     cout << "Vector was " << (IsVectorSorted(InVector) ? "" : "not ") << "sorted" << endl;
// }
//
// template <typename T>
// bool Test_Algo::IsVectorSorted(const vector<T>& InVector)
// {
//     bool bSorted = true;
//
//     for (size_t i = 1; i < InVector.size(); i++)
//     {
//         if (InVector[i - 1] > InVector[i])
//         {
//             bSorted = false;
//             break;
//         }
//     }
//     return bSorted;
// }
