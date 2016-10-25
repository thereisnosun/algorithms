#pragma once
#include "directed_graph.h"

struct PathWeight
{
    std::vector<std::shared_ptr<Edge>> m_vEdges;
    int m_iLeadNode;
    int m_iTotalScore;
    PathWeight();
    PathWeight(int iLeadNode, std::shared_ptr<Edge> pEdge);
    PathWeight(const PathWeight &weight);
    PathWeight(const PathWeight &&weight);
    PathWeight& operator =(const PathWeight &weight);
    PathWeight& operator =(const PathWeight &&weight);
    void AddEdge(int iLeadNode, std::shared_ptr<Edge> pEdge);
    friend bool operator <(const PathWeight &weight1, const PathWeight &weight2);
};



class DirectedWeightGraph: public DirectedGraph
{
public:
    DirectedWeightGraph()
    {
        m_GraphType = GraphType::DIRECTED_WEIGHT;
    }
    PathWeight FindShortestPath(int iNode1, int iNode2) const;
private:
    bool IfPathExists(int iLeadNode, std::shared_ptr<Edge> pEdge) const;
};
