#include "Test_NumbersAlgo.h"

#include <sstream>

#include "../Algo/AlgoNumbers.h"

Test_NumbersAlgo::Test_NumbersAlgo()
{
    TestName = "Numbers test";
}

void Test_NumbersAlgo::DefineTest()
{
    AddTest("Divides", [this]()
    {
        const int Multiple = 1231649;
        vector<int> Dividers;
        AlgoNumbers::GetDividers(Multiple, Dividers);

        if (Dividers.empty())
        {
            AddOutput("Multiple " + std::to_string(Multiple) + " has no dividers");
        }
        else
        {
            std::ostringstream str;
            std::copy(Dividers.begin(), Dividers.end() - 1, std::ostream_iterator<int>(str, " "));
            str << Dividers.back();
            
            AddOutput("Dividers for multiple " + std::to_string(Multiple) + " are: " + str.str());
        }
    });
    
    AddTest("Is number is prime", [this]()
    {
        const int Number = 1019;
        AddOutput("Number " + std::to_string(Number) + " is " + (AlgoNumbers::IsNumberIsPrime(Number) ? "" : "NOT ") + "prime!");
    });
    
    AddTest("Is number isn't prime", [this]()
    {
        const int Number = 1020;
        AddOutput("Number " + std::to_string(Number) + " is " + (AlgoNumbers::IsNumberIsPrime(Number) ? "" : "NOT ") + "prime!");
    });
    
    AddTest("Sieve of Eratosthenes", [this]()
    {
        const int MaxRange = 27;
        
        vector<int> PrimeNumbers;
        AlgoNumbers::SieveOfEratosthenes(MaxRange, PrimeNumbers);

        if (PrimeNumbers.empty())
        {
            AddOutput("No prime numbers in range 2 -> " + std::to_string(MaxRange) + "!");
            
        }
        else
        {
            bool bPrimeNumbers = true;
            for (const int& Number : PrimeNumbers)
            {
                if (!AlgoNumbers::IsNumberIsPrime(Number))
                {
                    bPrimeNumbers = false;
                    break;
                }
            }

            std::ostringstream str;
            std::copy(PrimeNumbers.begin(), PrimeNumbers.end() - 1, std::ostream_iterator<int>(str, " "));
            str << PrimeNumbers.back();
            
            if (!bPrimeNumbers)
            {
                AddOutput("PrimeNumbers in range 2 -> " + std::to_string(MaxRange) + " has NOT prime numbers!");    
                AddOutput("\nNumbers are: " + str.str());                                          
            }
            else
            {
                AddOutput("Prime numbers in range 2 -> " + std::to_string(MaxRange) + " are: " + str.str());                
            }
        }
    });
    
    AddTest("Factorization", [this]()
    {
        const int Number = 26;
        vector<int> Dividers;

        AlgoNumbers::Factorization(Number, Dividers);
        
        if (Dividers.empty())
        {
            AddOutput("No dividers was found for " + std::to_string(Number) + "!");            
        }
        else
        {
            std::ostringstream str;
            std::copy(Dividers.begin(), Dividers.end() - 1, std::ostream_iterator<int>(str, " "));
            str << Dividers.back();
            
            AddOutput("Dividers for " + std::to_string(Number) + " are: " + str.str());
        }
    });    
    
    AddTest("GCD school method", [this]()
    {
        const int First = 12;
        const int Second = 24;

        AlgoNumbers::GCDData<int> Data = AlgoNumbers::GCD_School(First, Second);
        AddOutput("GDC for numbers " + std::to_string(First) + " and " + std::to_string(Second) + " are " + std::to_string(Data.Lowest) + "(Lowest) and " + std::to_string(Data.Highest) + "(Highest)");
    });
    
    AddTest("GCD Euclidean method", [this]()
    {
        const int First = 12;
        const int Second = 24;

        const int Number = AlgoNumbers::GCD_Euclidean(First, Second);
        AddOutput("GDC for numbers " + std::to_string(First) + " and " + std::to_string(Second) + " is " + std::to_string(Number));
    });
    
    AddTest("LCM school method", [this]()
    {
        const int First = 16;
        const int Second = 24;

        const int Number = AlgoNumbers::LCM_School(First, Second);
        AddOutput("LCM for numbers " + std::to_string(First) + " and " + std::to_string(Second) + " is " + std::to_string(Number));
    });
    
    AddTest("LCM", [this]()
    {
        const int First = 16;
        const int Second = 24;

        const int Number = AlgoNumbers::LCM(First, Second);
        AddOutput("LCM for numbers " + std::to_string(First) + " and " + std::to_string(Second) + " is " + std::to_string(Number));
    });
}







