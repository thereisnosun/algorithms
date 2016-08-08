#pragma once
#include "graph.h"


class DirectedGraph : public Graph
{
public:
    std::map<int, int> TopologicalOrder() const;
    const std::vector<DirectedGraph>& ComputeSCC();
    bool IsAcyclic() const;
private:
    std::vector<DirectedGraph> m_vSCC;
};

