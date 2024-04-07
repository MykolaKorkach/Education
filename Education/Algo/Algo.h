#pragma once

#include <vector>

using std::vector;

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
                    T Temp = SortVector[j];
                    SortVector[j] = SortVector[j - 1];
                    SortVector[j - 1] = Temp;
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
                    T Temp = SortVector[j];
                    SortVector[j] = SortVector[j - 1];
                    SortVector[j - 1] = Temp;
                    bSwaped = true;
                }
            }
        }
    }
}
