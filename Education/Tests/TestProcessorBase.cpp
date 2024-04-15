#include "TestProcessorBase.h"

#include <chrono>

#include "TestBase.h"
#include "Test_NumbersAlgo.h"
#include "Test_SortAlgo.h"

TestProcessorBase* TestProcessorBase::TestProcessor = nullptr;

TestProcessorBase* TestProcessorBase::Get()
{
    if (TestProcessor == nullptr)
    {
        TestProcessor = new TestProcessorBase();
    }
    return TestProcessor;
}

void TestProcessorBase::RunTests()
{
    for (TestBase* Test : Tests)
    {
        if (!Test->CanRunTest())
        {
            continue;
        }
        
        cout << "===\t" << Test->GetName() << "\t===" << endl;
        
        while (Test->CanRunTest())
        {
            Test->OnTestStart();
            
            const vector<TestSpec> Specs = Test->GetTestSpecs();
        
            for (const TestSpec& Spec : Specs)
            {
                Test->AddOutput(Spec.SpecName + ":");
                
                Test->RunBefore();

                if (Spec.TestFunc != nullptr)
                {
                    Spec.TestFunc();
                }       

                if (Spec.TestPerfFunc != nullptr)
                {
                    StartTimer();
                    Spec.TestPerfFunc();
                    Test->AddOutput("Elapsed time: " + std::to_string(StopAndReturnElapsedTime()));
                }            

                if (Spec.TestResultFunc != nullptr)
                {
                    Spec.TestResultFunc();
                }
            
                Test->RunAfter();
                
                Test->PrintOutput();
            }

            Test->OnTestEnd();
        }        
    }
}

void TestProcessorBase::StartTimer()
{
    StartTime = std::chrono::steady_clock::now();
}

double TestProcessorBase::StopAndReturnElapsedTime() const
{
    const auto EndTime = std::chrono::steady_clock::now();
    const auto ElapsedTime = EndTime - StartTime;
    return std::chrono::duration_cast<std::chrono::duration<double>>(ElapsedTime).count();
}

TestProcessorBase::~TestProcessorBase()
{
    delete TestProcessor;

    for (const TestBase* Test : Tests)
    {
        delete Test;
    }
}

TestProcessorBase::TestProcessorBase()
{
    Tests.push_back(new Test_SortAlgo());
    Tests.push_back(new Test_NumbersAlgo());

    for (TestBase* Test : Tests)
    {
        Test->DefineTest();
    }
}
