#pragma once

#include <numeric>
#include <vector>

#include "AlgoSort.h"

using std::vector;

namespace AlgoNumbers
{
    template <typename T>
    struct GCDData
    {
        T Lowest;
        T Highest;
    };
    
    template<typename T>
    void GetDividers(T Multiple, vector<T>& OutDividers)
    {
        if (Multiple == 0)
        {
            return;
        }

        T Number = 1;
        vector<T> RightDividers;
        
        while (Number != static_cast<int>(sqrt(Multiple)) + 1)
        {
            if (Multiple % Number == 0)
            {
                OutDividers.push_back(Number);
                RightDividers.push_back(Multiple / Number);
            }
            ++Number;
        }
        
        OutDividers.insert(OutDividers.end(), RightDividers.rbegin(), RightDividers.rend() - 1);
    }

    
    template<typename T>
    bool IsNumberIsPrime(T Number)
    {
        if (Number == 0)
        {
            return false;
        }

        vector<T> Dividers;
        GetDividers(Number, Dividers);

        return Dividers.size() == 1;
    }

    
    template<typename T>
    void SieveOfEratosthenes(T EndRange, const vector<T>& InNumbers, vector<T>& OutPrimeNumbers)
    {
        if (EndRange == 0)
        {
            return;
        }
        
        vector<T> PrimeNumbers = InNumbers;

        int Count;

        for (int i = 0;; ++i)
        {
            if (EndRange < static_cast<int>(pow(PrimeNumbers[i], 2)))
            {
                Count = i;
                break;
            }
        }
        
        for (int i = 0; i < Count; ++i)
        {
            for (auto Begin = PrimeNumbers.begin(); Begin < PrimeNumbers.end();)
            {
                if (*Begin % PrimeNumbers[i] == 0 && *Begin > PrimeNumbers[i])
                {
                    Begin = PrimeNumbers.erase(Begin);
                }
                else
                {
                    ++Begin;
                }
            }
        }
        OutPrimeNumbers.clear();
        OutPrimeNumbers = PrimeNumbers;
    }

    
    template<typename T>
    void SieveOfEratosthenes(T EndRange, vector<T>& OutPrimeNumbers)
    {
        vector<T> Numbers(EndRange - 1);
        std::iota(Numbers.begin(), Numbers.end(), 2);
        
        SieveOfEratosthenes(EndRange, Numbers, OutPrimeNumbers);
    }

    template<typename T>
    void Factorization(T Number, vector<T>& OutDividers)
    {
        if (Number == 0)
        {
            return;
        }

        vector<T> PrimeNumbers;

        SieveOfEratosthenes(Number, PrimeNumbers);

        while (Number != 1)
        {
            for (size_t i = 0; i < PrimeNumbers.size(); ++i)
            {
                if (Number % PrimeNumbers[i] == 0)
                {
                    OutDividers.push_back(PrimeNumbers[i]);
                    Number /= PrimeNumbers[i];
                    break;
                }
            }
        }
    }

    template<typename T>
    GCDData<T> GCD_School(T FirstNumber, T SecondNumber)
    {
        vector<T> FirstDividers;
        Factorization(FirstNumber, FirstDividers);
        
        vector<T> SecondDividers;
        Factorization(SecondNumber, SecondDividers);

        AlgoSort::HeapSort(FirstDividers);
        AlgoSort::HeapSort(SecondDividers);
        
        GCDData<T> Data {1, 1};
        bool bLowest = false;
        size_t i = 0, j = 0;

        while (i != FirstDividers.size() && j != SecondDividers.size())
        {
            if (FirstDividers[i] == SecondDividers[j])
            {
                if (!bLowest)
                {
                    Data.Lowest = FirstDividers[i];
                    bLowest = true;
                }
                Data.Highest *= FirstDividers[i];
                
                i++;
                j++;
                continue;
            }

            if (FirstDividers[i] > SecondDividers[j] && j < SecondDividers.size() - 1)
            {
                j++;
            }
            else if (FirstDividers[i] < SecondDividers[j] && i < FirstDividers.size() - 1)
            {
                i++;
            }
        }

        return Data;
    }

    
    template<typename T>
    T GCD_Euclidean(T FirstNumber, T SecondNumber)
    {
        if (FirstNumber > SecondNumber)
        {
            std::swap(FirstNumber, SecondNumber);
        }

        while (SecondNumber > 0)
        {
            FirstNumber %= SecondNumber; 
            std::swap(FirstNumber, SecondNumber);
        }

        return FirstNumber;
    }
    
    template<typename T>
    T LCM_School(T FirstNumber, T SecondNumber)
    {
        if (FirstNumber > SecondNumber)
        {
            std::swap(FirstNumber, SecondNumber);
        }
        
        vector<T> FirstDividers;
        Factorization(FirstNumber, FirstDividers);
        
        vector<T> SecondDividers;
        Factorization(SecondNumber, SecondDividers);

        auto Begin = FirstDividers.begin();
        auto End = FirstDividers.end();

        for (const T& Elem : SecondDividers)
        {
            if (std::find(Begin, End, Elem) == End)
            {
                FirstNumber *= Elem;
            }
        }
        
        return FirstNumber;
    }

    template<typename T>
    T LCM(T FirstNumber, T SecondNumber)
    {        
        T GDC = GCD_Euclidean(FirstNumber, SecondNumber);
        
        return FirstNumber * SecondNumber / GDC;
    }
}

























