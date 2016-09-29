#pragma once
#include "directed_graph.h"

class DirectedWeightGraph: public DirectedGraph
{
public:
    DirectedWeightGraph()
    {
        m_GraphType = GraphType::DIRECTED_WEIGHT;
    }
};
