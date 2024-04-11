
#include "Tests/TestProcessorBase.h"

struct A
{
    int i;
    double d;
};
struct B
{
    double d;
    int i;
};

int main()
{

    TestProcessorBase* Processor = TestProcessorBase::Get();

    if (Processor != nullptr)
    {
        Processor->RunTests();
    }
    
    return 0;
}

