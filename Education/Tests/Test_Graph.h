#pragma once
#include "TestBase.h"

class Test_Graph : public TestBase
{
public:

    Test_Graph();
    virtual ~Test_Graph() override = default;
    
    void DefineTest() override;
};
