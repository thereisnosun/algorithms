#pragma once
#include <vector>
#include <map>

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
    int FindMinimumPath(int iNode1, int iNode2) const;
private:
    void BuildFromMatrix(const std::vector<std::vector<int>> &vAdjMatrix);
	void BuildFromVectorList(const std::vector<std::vector<int>> &vAdjMatrix);
	
    void AddUniquePair(int, int);
	GraphRepresentation CheckRepresentation(const std::vector<std::vector<int>> &vAdjMatrix) const;
private:
    
    std::vector<std::pair<int, int> > m_vAdjacencyVector; //use list instead of vector ?
    int m_iVertexNum;
};


//by simple meant undirected unweight graph
class SimpleGraph: public Graph
{

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
    std::multimap<std::pair<int, int>, bool> m_mEdges;
};

class WeightGraph
{
public:
    WeightGraph()
    {
    }
private:
    std::multimap<std::pair<int, int>, int> m_mEdges;
};

