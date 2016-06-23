#pragma once
#include "graph.h"


class DirectedGraph : public Graph
{
public:
    std::map<int, int> TopologicalOrder() const;
    std::vector<std::vector<int>> ComputeSCC() const;
    bool IsAcyclic() const;
};

