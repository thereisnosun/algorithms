#include "directed_weight_graph.h"
#include <algorithm>
#include <iterator>
#include <iostream>

struct EdgeWeight
{
    std::vector<std::shared_ptr<Edge>> m_vEdges;
    int iTotalScore;
};

std::shared_ptr<DirectedWeightGraph> DirectedWeightGraph::FindShortestPath(int iNode1, int iNode2) const
{
    std::shared_ptr<DirectedWeightGraph> pPath;

    std::vector<std::shared_ptr<Edge>> vLocalEdges;
    vLocalEdges.reserve(m_vEdges.size());
    std::copy(m_vEdges.begin(), m_vEdges.end(), std::back_inserter(vLocalEdges));

    std::make_heap(vLocalEdges.begin(), vLocalEdges.end());
    std::sort_heap(vLocalEdges.begin(), vLocalEdges.end(),
                   [](const std::shared_ptr<Edge> pEdge1, const std::shared_ptr<Edge> pEdge2) -> bool
    {
        return pEdge1->Weight() < pEdge2->Weight();
    });
   // std::sort_heap(vLocalEdges.begin(), vLocalEdges.end());


    auto itFind = std::find_if(vLocalEdges.begin(), vLocalEdges.end(), 
                               [&iNode1](const std::shared_ptr<Edge> pEdge) -> bool
    {
        if (pEdge->First() == iNode1 && pEdge->Direction() == EdgeDirection::FIRST_TO_SECOND)
        {
            return true;
        }

        if (pEdge->Second() == iNode1 && pEdge->Direction() == EdgeDirection::SECOND_TO_FIRST)
        {
            return true;
        }

        return false;
    });

    if (itFind != std::end(vLocalEdges))
    {
        std::cout << "Edge is not present in the graph!\n";
    }

    return pPath;
}