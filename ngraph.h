#pragma once
#include "edge.h"
#include <vector>
#include <memory>



//TODO: determine type of graph depending on constructor which was called
//and then allow only that graph-specific types
class NGraph
{
public:
    NGraph()
    {
    }
    NGraph(const std::vector<std::vector<int>> &vAdjMatrix);
    size_t FindMinimumCut() const;
    void AddEdge(Edge *edge);
    void AddVertex();
private:
    std::vector<std::unique_ptr<Edge>> m_vEdges;
    int m_iNumVertex;
};