#include "Test_GraphAlgo.h"

#include <sstream>
#include <stack>

#include "../Algo/AlgoGraph.h"

Test_GraphAlgo::Test_GraphAlgo()
{
    TestName = "Graph algo";
}

void Test_GraphAlgo::DefineTest()
{
    auto FibonacciGraph = [this]()
    {
        AlgoGraph::CreateFibonacciGraph(Graph, 1000);
    };
    
    auto CompleteGraph = [this]()
    {
        AlgoGraph::CreateCompleteGraph(Graph, 100);
    };
    
    auto ComponentGraph = [this]()
    {
        AlgoGraph::CreateComponentGraph(Graph, 100);
    };

    
    AddTest("Check complete graph", [this, CompleteGraph]()
    {
        CompleteGraph();        
        
        AddOutput("The graph is " + std::string(AlgoGraph::IsGraphComplete(Graph) ? "" : "NOT ") + "complete!");
    });
    

    TestSpec DSF("Depth search first");
    DSF.PreTestPerfFunc = CompleteGraph;
    DSF.TestPerfFunc = [this]()
    {        
        std::vector<size_t> VisitedIndexes;
        AlgoGraph::DFS(Graph, 0, VisitedIndexes);

        AddOutput("Visited " + std::to_string(VisitedIndexes.size()) + "/" + std::to_string(Graph.GetSize()) + " elements");
    };
    AddTestSpec(DSF);

    
    TestSpec BSF("Breadth search first");
    BSF.PreTestPerfFunc = CompleteGraph;
    BSF.TestPerfFunc = [this]()
    {        
        std::vector<size_t> VisitedIndexes;
        AlgoGraph::BFS(Graph, 0, VisitedIndexes);

        AddOutput("Visited " + std::to_string(VisitedIndexes.size()) + "/" + std::to_string(Graph.GetSize()) + " elements");
    };
    AddTestSpec(BSF);

    
    AddTest("Check component graph", [this, ComponentGraph]()
    {
        ComponentGraph();

        const int ComponentCount = AlgoGraph::GetConnectedComponentCount(Graph);
        
        AddOutput("Graph has " + std::to_string(ComponentCount) + " components!");
    });
    
    AddTest("Check fibonacci graph", [this, FibonacciGraph]()
    {
        FibonacciGraph();

        const int ComponentCount = AlgoGraph::GetConnectedComponentCount(Graph);
        
        AddOutput("Graph has " + std::to_string(ComponentCount) + " components!");
    });
    
    AddTest("BSF path search", [this, FibonacciGraph]()
    {
        FibonacciGraph();

        std::vector<size_t> Path;
        AlgoGraph::BFS_PathSearch(Graph, 10, Graph.GetSize() - 1, Path);

        if (Path.empty())
        {
            AddOutput("Path was not found!");
        }
        else
        {
            std::ostringstream str;
            std::copy(Path.begin(), Path.end() - 1, std::ostream_iterator<int>(str, " "));
            str << Path.back();
        
            AddOutput("Path size is " + std::to_string(Path.size()) + ". Path are: " + str.str());
        }
    });
}
