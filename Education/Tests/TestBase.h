#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::function;
using std::cout;
using std::endl;

struct TestSpec
{
    TestSpec() = delete;
    TestSpec(const string& InSpecName)
    {
        SpecName = InSpecName;
    }

    bool IsValid() const
    {
        return !SpecName.empty();
    }
    
    string SpecName;
    function<void()> TestFunc;
    function<void()> PreTestPerfFunc;
    function<void()> TestPerfFunc;
    function<void()> TestResultFunc;
};


struct TestBase
{
    virtual void DefineTest() = 0;

    bool IsValid() const;
    string GetName() const { return TestName; }

    virtual ~TestBase() = default;

    virtual bool CanRunTest() const;
    
    virtual void OnTestStart();
    virtual void OnTestEnd();
    
    void RunBefore() const;
    void RunAfter() const;

    const vector<TestSpec>& GetTestSpecs() const { return TestSpecs; }

    void AddOutput(const string& OutputStr);
    void PrintOutput();
    
protected:
    
    void SetBeforeTestFunc(const function<void()>& BeforeFunc);
    void SetAfterTestFunc(const function<void()>& AfterFunc);
    
    void AddTestSpec(TestSpec Spec);

    void AddTest(const string& SpecName, const function<void()>& InTestFunc);
    void AddPerfTest(const string& SpecName, const function<void()>& InPerfFunc);
    void AddPerfTestWithResult(const string& SpecName, const function<void()>& InPerfFunc, const function<void()>& InResultFunc);

    int CurrentStage = 0;
    int MaxStage = 1;
    
    string TestName;
    string TestOutput;
    
private:    
    
    function<void()> Before;
    function<void()> After;
    vector<TestSpec> TestSpecs;
};
