#pragma once
#include "graph.h"


class DirectedGraph : public Graph
{
public:
    std::map<int, int> TopologicalOrder() const;
    bool IsAcyclic() const;
};

