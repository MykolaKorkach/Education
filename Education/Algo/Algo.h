#pragma once

#include <map>
#include <vector>

using std::vector;
using std::map;
using std::swap;
using std::iter_swap;

namespace AlgoSort
{
    template<typename T>
    void BubbleSort(vector<T>& SortVector)
    {
        if (SortVector.empty())
        {
            return;
        }
        
        const size_t Size = SortVector.size();
        for (size_t i = 0; i < Size; i++)
        {
            for (size_t j = 1; j < Size - i; j++)
            {
                if (SortVector[j - 1] > SortVector[j])
                {
                    swap(SortVector[j], SortVector[j - 1]);
                }
            }
        }
    }
    
    template<typename T>
    void BubbleSortAdaptive(vector<T>& SortVector)
    {
        if (SortVector.empty())
        {
            return;
        }

        bool bSwaped = true;
        const size_t Size = SortVector.size();
        for (size_t i = 0; i < Size; i++)
        {
            if (!bSwaped)
            {
                break;
            }
            bSwaped = false;
            
            for (size_t j = 1; j < Size - i; j++)
            {
                if (SortVector[j - 1] > SortVector[j])
                {
                    swap(SortVector[j], SortVector[j - 1]);
                    bSwaped = true;
                }
            }
        }
    }
    
    template<typename T>
    void InsertionSort(vector<T>& SortVector)
    {
        if (SortVector.empty())
        {
            return;
        }
        
        const size_t Size = SortVector.size();
        for (size_t i = 1; i < Size; i++)
        {
            if (SortVector[i - 1] > SortVector[i])
            {
                size_t j = 0;
                while (j < i)
                {
                    if (SortVector[j] > SortVector[i])
                    {
                        std::rotate(SortVector.rend() - i - 1, SortVector.rend() - i, SortVector.rend() - j);
                        break;
                    }
                    j++;
                }
            }
        }
    }

    
    template<typename T>
    void CountingSort(const vector<T>& InSortVector, vector<T>& OutSortVector)
    {
        if (InSortVector.empty())
        {
            return;
        }
        
        map<T, int> CountMap;
        
        const size_t Size = InSortVector.size();
        for (size_t i = 1; i < Size; i++)
        {
            int& Count = CountMap[InSortVector[i]];
            ++Count;
        }

        for (auto& [Element, Count] : CountMap)
        {
            for (int i = 0; i < Count; i++)
            {
                OutSortVector.push_back(Element);
            }
        }
    }
    
    template<typename T>
    void CountingStableSort(const vector<T>& InSortVector, vector<T>& OutSortVector)
    {
        struct SortData
        {
            int Count = 0;
            int StartingIndex = 0;
        };
        
        if (InSortVector.empty())
        {
            return;
        }

        OutSortVector.resize(InSortVector.size());
        map<T, SortData> CountMap;
        
        const size_t Size = InSortVector.size();
        for (size_t i = 0; i < Size; i++)
        {
            ++(CountMap[InSortVector[i]].Count);
        }

        int NextStartIndex = 0;
        for (auto& [Element, Data] : CountMap)
        {
            Data.StartingIndex = NextStartIndex;
            NextStartIndex += Data.Count;
        }

        for (const T& Element : InSortVector)
        {
            SortData& Data = CountMap[Element];
            OutSortVector[Data.StartingIndex] = Element;
            ++Data.StartingIndex;
        }
    }
    
    
    template<typename Iter>
    void QuickLomutoSort(Iter Begin, Iter End)
    {        
        auto IterI = Begin;
        auto IterJ = Begin;
        auto IterEnd = End - 1;
        
        std::iter_swap(Begin + rand() % (End - Begin), IterEnd);
        
        while (IterJ != End)
        {
            if (*IterJ < *IterEnd)
            {
                std::iter_swap(IterI, IterJ);
                ++IterI;
            }
            ++IterJ;
        }
        std::iter_swap(IterI, IterEnd);

        if ((IterI - Begin) > 1)
        {            
            QuickLomutoSort(Begin, IterI);
        }
        if ((End - IterI) > 1)
        {            
            QuickLomutoSort(IterI + 1, End);
        }
    }
    
    template<typename T>
    void QuickLomutoSort(vector<T>& InSortVector)
    {
        if (InSortVector.size() > 1)
        {
            QuickLomutoSort(InSortVector.begin(), InSortVector.end());
        }
    }
    
    template<typename Iter>
    void QuickHoareSort(Iter Begin, Iter End)
    {        
        auto IterI = Begin;
        auto IterJ = End - 1;
        auto IterBase = Begin + rand() % (End - Begin);

        while (true)
        {
            while (*IterI < *IterBase)
            {
                ++IterI;
            }
            while (*IterJ > *IterBase)
            {
                --IterJ;
            }

            if (IterI >= IterJ)
            {
                break;
            }

            if (IterBase == IterI || IterBase == IterJ)
            {
                IterBase = IterBase == IterI ? IterJ : IterI;
            }
            std::iter_swap(IterI, IterJ);
        }

        if ((IterI - Begin) > 1)
        {            
            QuickHoareSort(Begin, IterI);
        }
        if ((End - IterI) > 1)
        {            
            QuickHoareSort(IterI + 1, End);
        }
    }
    
    template<typename T>
    void QuickHoareSort(vector<T>& InSortVector)
    {
        if (InSortVector.size() > 1)
        {
            QuickHoareSort(InSortVector.begin(), InSortVector.end());
        }
    }
}

















