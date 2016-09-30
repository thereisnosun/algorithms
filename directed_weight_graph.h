#pragma once
#include "directed_graph.h"

class DirectedWeightGraph: public DirectedGraph
{
public:
    DirectedWeightGraph()
    {
        m_GraphType = GraphType::DIRECTED_WEIGHT;
    }
    std::shared_ptr<DirectedWeightGraph> FindShortestPath(int iNode1, int iNode2) const;
};
