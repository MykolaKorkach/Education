
#include "Tests/TestProcessorBase.h"

int main()
{    
    TestProcessorBase* Processor = TestProcessorBase::Get();

    if (Processor != nullptr)
    {
        Processor->RunTests();
    }
    
    return 0;
}

