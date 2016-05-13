#pragma once
#include <vector>

class Graph
{
public:
    Graph(const std::vector<std::vector<int>> &vAdjMatrix);
    void AddEdge(const std::pair<int, int> &edge);
    void AddVertex(const std::vector<int> &vVertex);
private:
    void BuildFromMatrix(const std::vector<std::vector<int>> &vAdjMatrix);
    void AddUniquePair(int, int);
private:
    
    std::vector<std::pair<int, int> > m_vAdjacencyVector; 
    int m_iVertexNum;
};