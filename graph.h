#pragma once
#include <vector>

enum class GraphRepresentation
{
	NONE,
	MATRIX,
	VECTOR_LIST
};


class Graph
{
public:
    Graph(const std::vector<std::vector<int>> &vAdjMatrix);
    void AddEdge(const std::pair<int, int> &edge);
    void AddVertex(const std::vector<int> &vVertex);
    std::vector<std::pair<int, int>> FindMinimumCut() const;
    std::vector<std::pair<int, int>> FindMinimumPath(int iNode1, int iNode2) const;
private:
    void BuildFromMatrix(const std::vector<std::vector<int>> &vAdjMatrix);
	void BuildFromVectorList(const std::vector<std::vector<int>> &vAdjMatrix);
	
    void AddUniquePair(int, int);
	GraphRepresentation CheckRepresentation(const std::vector<std::vector<int>> &vAdjMatrix) const;
private:
    
    std::vector<std::pair<int, int> > m_vAdjacencyVector; //use list instead of vector ?
    int m_iVertexNum;
};

//how direction can be represented?
//first vertex of the pair is the starting point ?
class DirectedGraph /*: public Graph*/
{
public:
    DirectedGraph()
    {
    }
private:
};

class WeightGraph
{
public:
    WeightGraph()
    {
    }
};

