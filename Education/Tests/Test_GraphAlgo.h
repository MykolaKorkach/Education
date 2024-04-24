#pragma once
#include "TestBase.h"
#include "../Structures/Graph.h"


class Test_GraphAlgo : public TestBase
{
public:
    Test_GraphAlgo();
    virtual ~Test_GraphAlgo() override = default;
    
    void DefineTest() override;

private:

    Graph_Matrix<int> Graph;
};
