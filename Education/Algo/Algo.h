#pragma once

#include <map>
#include <vector>

using std::vector;
using std::map;

namespace Algo
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
                    std::swap(SortVector[j], SortVector[j - 1]);
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
                    std::swap(SortVector[j], SortVector[j - 1]);
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
            auto Index = OutSortVector.begin() + Data.StartingIndex;
            OutSortVector.erase(OutSortVector.begin() + Data.StartingIndex);
            OutSortVector.insert(OutSortVector.begin() + Data.StartingIndex, Element);
            Data.StartingIndex += 1;
        }
    }
}

















