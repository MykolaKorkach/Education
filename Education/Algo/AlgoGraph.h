#pragma once
#include <queue>

#include "../Structures/Graph.h"


namespace AlgoGraph
{
    template<typename T>
    void CreateFibonacciGraph(Graph_Matrix<T>& OutGraph, size_t ElementsNum)
    {
        OutGraph.Clear();
        OutGraph.SetGraphSize(ElementsNum);
        
        size_t PrevNumber = 1;
        size_t CurrentNumber = 1;
        size_t CurrentConnectionCount = 1;
        
        for (size_t Index = 0; Index < ElementsNum; Index++)
        {                     
            std::vector<size_t> Connections;
            OutGraph.GetConnections(Index, Connections);

            while (Connections.size() < CurrentConnectionCount)
            {
                const size_t Module = PrevNumber > Index ? PrevNumber - Index : Index - PrevNumber;
                if (Module > 0)
                {
                    const size_t ConnectionIndex = ElementsNum % Module;
                    if (ConnectionIndex != Index)
                    {                    
                        Connections.push_back(ConnectionIndex);
                    }
                }
                
                PrevNumber = CurrentNumber;
                CurrentNumber += PrevNumber;
                if (CurrentNumber > ElementsNum)
                {
                    PrevNumber = 1;
                    CurrentNumber = 1;
                }
            }

            if (++CurrentConnectionCount > 3)
            {
                CurrentConnectionCount = 1;
            }
            
            OutGraph.AddNode(Index, Connections);
        }
    }
    
    template<typename T>
    void CreateCompleteGraph(Graph_Matrix<T>& OutGraph, int ElementsNum)
    {
        OutGraph.Clear();
        OutGraph.SetGraphSize(ElementsNum);
        
        std::vector<size_t> Connections;
        for (size_t Index = 0; Index < ElementsNum; Index++)
        {            
            OutGraph.AddNode(Index, Connections);
            Connections.push_back(Index);
        }
    }
    
    template<typename T>
    void CreateComponentGraph(Graph_Matrix<T>& OutGraph, int ElementsNum)
    {
        OutGraph.Clear();
        OutGraph.SetGraphSize(ElementsNum);
        
        int ComponentNodeCount = 1;        
        std::vector<size_t> Connections;
        
        for (size_t Index = 0; Index < ElementsNum; Index++)
        {
            if (ComponentNodeCount == Index)
            {
                Connections.clear();
                ComponentNodeCount *= 2;
            }
            
            OutGraph.AddNode(Index, Connections);
            Connections.push_back(Index);
        }
    }

    template<typename T>
    void DFS(const Graph_Matrix<T>& InGraph, size_t StartIndex, std::vector<size_t>& OutVisited)
    {
        std::stack<size_t> Path;

        Path.push(StartIndex);
        OutVisited.push_back(StartIndex);

        while (!Path.empty())
        {
            std::vector<size_t> Connections;

            InGraph.GetConnections(Path.top(), Connections);

            bool bFound = false;
            for (size_t Connection : Connections)
            {
                if (std::find(OutVisited.begin(), OutVisited.end(), Connection) == OutVisited.end())
                {
                    OutVisited.push_back(Connection);
                    Path.push(Connection);
                    bFound = true;
                    break;
                }
            }
            if (bFound == false)
            {
                Path.pop();
            }
        }
    }

    template<typename T>
    void BFS(const Graph_Matrix<T>& InGraph, size_t StartIndex, std::vector<size_t>& OutVisited)
    {
        std::queue<size_t> PathQueue;

        PathQueue.push(StartIndex);
        OutVisited.push_back(StartIndex);

        while (!PathQueue.empty())
        {            
            std::vector<size_t> Connections;

            InGraph.GetConnections(PathQueue.front(), Connections);
            
            for (size_t Connection : Connections)
            {
                if (std::find(OutVisited.begin(), OutVisited.end(), Connection) == OutVisited.end())
                {
                    OutVisited.push_back(Connection);
                    PathQueue.push(Connection);
                }
            }
            PathQueue.pop();
        }
    }

    
    template<typename T>
    void BFS_PathSearch(const Graph_Matrix<T>& InGraph, size_t StartIndex, size_t EndIndex, std::vector<size_t>& OutPath)
    {
        if (StartIndex == EndIndex || !InGraph.IsValidIndex(StartIndex) || !InGraph.IsValidIndex(EndIndex))
        {
            return;
        }

        std::vector<size_t> Parents(InGraph.GetSize(), StartIndex);
        std::vector<size_t> Visited;
        std::queue<size_t> PathQueue;

        PathQueue.push(StartIndex);
        Visited.push_back(StartIndex);

        size_t LastIndex = 0;
        while (!PathQueue.empty())
        {
            LastIndex = PathQueue.front();
            PathQueue.pop();
            if (LastIndex == EndIndex)
            {
                break;
            }
            
            std::vector<size_t> Connections;

            InGraph.GetConnections(LastIndex, Connections);
            
            for (size_t Connection : Connections)
            {
                if (std::find(Visited.begin(), Visited.end(), Connection) == Visited.end())
                {
                    Parents[Connection] = LastIndex;
                    Visited.push_back(Connection);
                    PathQueue.push(Connection);
                }
            }
        }

        OutPath.push_back(LastIndex);
        while (OutPath.back() != StartIndex)
        {
            LastIndex = Parents[LastIndex];
            OutPath.push_back(LastIndex);
        }
        
        std::ranges::reverse(OutPath.begin(), OutPath.end());
    }


    template<typename T>
    bool IsGraphComplete(const Graph_Matrix<T>& InGraph)
    {
        bool bCompleteGraph = true;
        vector<size_t> Connections;
        const size_t GraphSize = InGraph.GetSize();
        for (size_t Index = 0; Index < GraphSize; Index++)
        {
            InGraph.GetConnections(Index, Connections);
            if (Connections.size() != GraphSize - 1)
            {
                bCompleteGraph = false;
                break;
            }

            size_t Offset = 0;
            for (size_t ConnectionIndex = 0; ConnectionIndex < Connections.size(); ConnectionIndex++)
            {                
                if (Connections[ConnectionIndex - Offset] != ConnectionIndex)
                {
                    if (ConnectionIndex == Index)
                    {
                        Offset = 1;
                        continue;
                    }
                    
                    bCompleteGraph = false;
                    break;
                }
            }
            Connections.clear();
        }

        return bCompleteGraph;
    }
    
    
    template<typename T>
    int GetConnectedComponentCount(const Graph_Matrix<T>& InGraph)
    {
        int ConnectedComponentCount = 0;
        std::vector<bool> Visited(InGraph.GetSize(), false);

        for (size_t Index = 0; Index < Visited.size(); Index++)
        {
            if (Visited[Index] == false)
            {
                std::vector<size_t> VisitedNodes;
                DFS(InGraph, Index, VisitedNodes);

                for (const size_t& VisitedIndex : VisitedNodes)
                {
                    Visited[VisitedIndex] = true;                    
                }
                ConnectedComponentCount++;
            }
        }

        return ConnectedComponentCount;
    }
}






