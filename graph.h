#pragma once
#include <vector>
#include <map>

enum class GraphRepresentation
{
	NONE,
	MATRIX,
	VECTOR_LIST
};


class IGraph
{
public:
	virtual size_t FindMinimumCut() const = 0;

};

//TODO: implement DFS
//this will be the very basic grapsh representation
class Graph: public IGraph
{
public:
    Graph(const std::vector<std::vector<int>> &vAdjMatrix);
    void AddEdge(const std::pair<int, int> &edge);
    void AddVertex(const std::vector<int> &vVertex);
    size_t FindMinimumCut() const;
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


