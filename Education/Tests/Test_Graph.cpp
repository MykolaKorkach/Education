#include "Test_Graph.h"

#include "../Structures/Graph.h"

Test_Graph::Test_Graph()
{
    TestName = "Graph test";
}

void Test_Graph::DefineTest()
{
    AddTest("Graph add new element", [this]()
    {
        Graph_Matrix<int> Graph;
        Graph.AddNode(5);
        
        AddOutput("New element was " + std::string(Graph.GetSize() == 1 ? "" : "NOT ") + "added!");
        
        Graph.AddNode(3);
        
        AddOutput("Second element was " + std::string(Graph.GetSize() == 2 ? "" : "NOT ") + "added!");
    });
    
    AddTest("Graph check connections", [this]()
    {
        Graph_Matrix<int> Graph;
        size_t NewNodeIndex = Graph.AddNode(5);
        Graph.AddNode(3, {NewNodeIndex});        

        std::vector<size_t> Connections;
        Graph.GetConnections(NewNodeIndex, Connections);
        
        AddOutput("Connection was " + std::string(Connections.empty() ? "NOT " : "") + "added!");
        AddOutput("Connection is " + std::string(Graph[Connections[0]] == 5 ? "NOT " : "") + "correct!");
    });
    
    AddTest("Graph remove node", [this]()
    {
        Graph_Matrix<int> Graph;
        Graph.AddNode(5);
        Graph.RemoveNode(0);        
        AddOutput("Node was " + std::string(Graph.Empty()  ? "" : "NOT ") + "removed!");
        
        Graph.AddNode(0);
        Graph.AddNode(1, {0});
        Graph.AddNode(2, {0, 1});
        
        Graph.RemoveNode(2);        
        std::vector<size_t> Connections;
        Graph.GetConnections(0, Connections);

        AddOutput("Connection is " + std::string(Connections.size() == 1 && Graph[Connections[0]] == 1 ? "" : "NOT ") + "correct!");
    });
    
    AddTest("Graph remove connection", [this]()
    {
        Graph_Matrix<int> Graph;
        
        Graph.AddNode(0);
        Graph.AddNode(1, {0});
        Graph.AddNode(2, {0, 1});
        
        Graph.RemoveConnection(2, {0, 1});        
        std::vector<size_t> Connections;
        Graph.GetConnections(0, Connections);

        AddOutput("Connection was " + std::string(Connections.size() == 1 && Graph[Connections[0]] == 1 ? "" : "NOT ") + "removed!");
    });
}











