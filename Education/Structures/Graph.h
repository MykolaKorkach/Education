#pragma once
#include <vector>



template<typename T>
class Graph_Matrix
{
public:

    void SetGraphSize(size_t ElementNum)
    {
        Elements.resize(ElementNum, T());
        AdjacencyMatrix.resize(ElementNum);

        for (auto& Vector : AdjacencyMatrix)
        {
            Vector.resize(ElementNum, false);
        }
    }
    
    size_t AddNode(const T& NewElement)
    {
        if (LastIndex >= Elements.size())
        {
            SetGraphSize(LastIndex + 1);
        }
        
        Elements[LastIndex] = NewElement;
        return LastIndex++;        
    }
    
    void RemoveNode(const size_t& RemoveElementIndex)
    {
        if (RemoveElementIndex < 0 || RemoveElementIndex > Elements.size())
        {
            return;
        }

        Elements.erase(Elements.begin() + RemoveElementIndex);
        AdjacencyMatrix.erase(AdjacencyMatrix.begin() + RemoveElementIndex);

        for (auto& Vector : AdjacencyMatrix)
        {
            Vector.erase(Vector.begin() + RemoveElementIndex);
        }
        
        LastIndex--;        
    }
    
    void AddNode(const T& NewElement, const std::vector<size_t>& InConnections)
    {
        const size_t NewIndex = AddNode(NewElement);        

        AddConnection(NewIndex, InConnections);
    }

    void AddConnection(size_t ElementIndex, const std::vector<size_t>& NewConnections)
    {
        for (const size_t& ConnectionIndex : NewConnections)
        {
            AdjacencyMatrix[ElementIndex][ConnectionIndex] = true;
        }

        for (const size_t& ConnectionIndex : NewConnections)
        {
            AdjacencyMatrix[ConnectionIndex][ElementIndex] = true;
        }
    }

    void RemoveConnection(size_t ElementIndex, const std::vector<size_t>& RemoveConnections)
    {
        for (const size_t& ConnectionIndex : RemoveConnections)
        {
            AdjacencyMatrix[ElementIndex][ConnectionIndex] = false;
        }

        for (const size_t& ConnectionIndex : RemoveConnections)
        {
            AdjacencyMatrix[ConnectionIndex][ElementIndex] = false;
        }
    }

    void GetConnections(size_t ElementIndex, std::vector<size_t>& OutConnections) const
    {
        const std::vector<bool>& ConnectionRow = AdjacencyMatrix[ElementIndex];

        for (size_t Index = 0; Index < ConnectionRow.size(); Index++)
        {
            if (ConnectionRow[Index] == true)
            {
                OutConnections.push_back(Index);
            }
        }
    }

    bool IsValidIndex(size_t Index) const
    {
        return Index < LastIndex;
    }
    
    T& operator[](size_t Index)
    {
        return Elements[Index];
    }
    
    size_t GetSize() const { return LastIndex; }
    bool Empty() const { return LastIndex == 0; }

    void Clear()
    {
        Elements.clear();
        AdjacencyMatrix.clear();
        LastIndex = 0;
    }
    
private:

    size_t LastIndex = 0;
    
    std::vector<T> Elements;
    std::vector<std::vector<bool>> AdjacencyMatrix;

};













