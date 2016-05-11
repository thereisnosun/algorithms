#pragma once
#include <vector>

class Graph
{
public:
    Graph(const std::vector<std::vector<int>> &vAdjMatrix);
private:
    void BuildFromMatrix(const std::vector<std::vector<int>> &vAdjMatrix);
    void AddUniquePair(int, int);
private:
    
    std::vector<std::pair<int, int> > m_vAdjacencyVector; 
};