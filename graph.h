#pragma once
#include "edge.h"
#include <vector>
#include <memory>



//TODO: determine type of graph depending on constructor which was called
//and then allow only that graph-specific types
class Graph
{
public:
    Graph()
    {
    }
    Graph(const std::vector<std::vector<int>> &vAdjMatrix);
    size_t FindMinimumCut() const;
    int FindMinimumPath(int iNode1, int iNode2) const;
    void AddEdge(Edge *edge);
    void AddEdge(int iVert1, int iVert2);
    void AddVertex(const std::vector<int> &vAdjency);
private:
    void AddUniquePair(int m, int n);
private:
    std::vector<std::shared_ptr<Edge>> m_vEdges;
    int m_iNumVertex;
};