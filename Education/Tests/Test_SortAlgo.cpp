#include "Test_SortAlgo.h"

#include "../Algo/AlgoSort.h"

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
    
    AddPerfTest("Heap sort", [this]()
    {
        AlgoSort::HeapSort(VectorInt);
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





