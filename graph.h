#pragma once
#include "edge.h"
#include <vector>
#include <memory>
#include <functional>
#include <set>


//TODO: determine type of graph depending on constructor which was called
//and then allow only that graph-specific types(some cool stuff with templates)


enum class GraphType
{
    NORMAL = 1,
    DIRECTED,
    WEIGHT,
    DIRECTED_WEIGHT
};

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
    void AddEdge(int iVert1, int iVert2); //this one breaks hierchy structure, what if it is called within DirectedWeightGraph ?
    void AddVertex(const std::vector<int> &vAdjency);
    
public:
    //these should be "working horses" of the class, 
    //actual usage should be done by user routines which use them for common purposes
    void BFS(int iNode, std::function<void(int iNode1, int iNode2)> workFunc) const;
    void DFS(int iNode, std::function<void(std::shared_ptr<Edge> edge)> workFunc) const;
private:
    void AddUniqueEdge(Edge *edge);
    void AddUniqueVertex(int iVertex);
protected:
    std::vector<std::shared_ptr<Edge>> m_vEdges;
    std::set<int> m_sVertex;
    int m_iNumVertex;
    GraphType m_GraphType;
};

class DirectedGraph : public Graph
{
public:
    std::map<int, int> TopologicalOrder() const;
    bool IsAsyclic() const;
};