#include "TestBase.h"

void TestBase::AddOutput(const string& OutputStr)
{
    TestOutput.append(OutputStr + "\t");
}

void TestBase::PrintOutput()
{    
    cout << TestOutput << endl;
    TestOutput.clear();
}

void TestBase::SetBeforeTestFunc(const function<void()>& BeforeFunc)
{
    Before = BeforeFunc;
}

void TestBase::SetAfterTestFunc(const function<void()>& AfterFunc)
{
    After = AfterFunc;
}

void TestBase::AddTestSpec(TestSpec Spec)
{
    if (Spec.IsValid())
    {
        TestSpecs.push_back(Spec);
    }
}

void TestBase::AddTest(const string& SpecName, const function<void()>& InTestFunc)
{
    TestSpec Spec(SpecName);
    Spec.TestFunc = InTestFunc;    
    TestSpecs.push_back(Spec);
}

void TestBase::AddPerfTest(const string& SpecName, const function<void()>& InPerfFunc)
{
    TestSpec Spec(SpecName);
    Spec.TestPerfFunc = InPerfFunc;    
    TestSpecs.push_back(Spec);
}

void TestBase::AddPerfTestWithResult(const string& SpecName, const function<void()>& InPerfFunc, const function<void()>& InResultFunc)
{
    TestSpec Spec(SpecName);
    Spec.TestPerfFunc = InPerfFunc;
    Spec.TestResultFunc = InResultFunc;
    TestSpecs.push_back(Spec);
}


bool TestBase::IsValid() const
{
    return !TestSpecs.empty() && !TestName.empty();
}

bool TestBase::CanRunTest() const
{
    return IsValid() && CurrentStage < MaxStage;
}

void TestBase::OnTestStart()
{
    cout << "Stage " << CurrentStage << " was started." << endl;
}

void TestBase::OnTestEnd()
{
    cout << "Stage " << CurrentStage << " was ended.\n" << endl;
    CurrentStage++;
}

void TestBase::RunBefore() const
{
    if (Before != nullptr)
    {
        Before();
    }
}

void TestBase::RunAfter() const
{
    if (After != nullptr)
    {
        After();
    }
}


