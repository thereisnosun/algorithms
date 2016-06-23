#include "directed_graph.h"



std::vector<std::vector<int>> DirectedGraph::ComputeSCC() const
{
    std::vector<std::vector<int>> vSCC;

    //DFS()

    return std::move(vSCC);
}

std::map<int, int> DirectedGraph::TopologicalOrder() const
{
    std::map<int, int> mOrder;

    //find sink vertix, vertix which has not outgoing arcs
    //direction should be taken to consideration
    int iFirstNode = m_iNumVertex; //currently assuming first node equals 1;
    int iCurrLabel = m_iNumVertex;
    DFS(iFirstNode, [&mOrder, &iCurrLabel](std::shared_ptr<Edge> edge) -> void
    {
        EdgeDirection direction = edge->Direction();
        std::pair<std::map<int, int>::iterator, bool> retVal;
        //if (direction == EdgeDirection::FIRST_TO_SECOND)
        //    retVal = mOrder.insert(std::make_pair(edge->Second(), iCurrLabel));
        //else
        //    retVal = mOrder.insert(std::make_pair(edge->First(), iCurrLabel));


        retVal = mOrder.insert(std::make_pair(edge->Second(), iCurrLabel));
        if (retVal.second)
            --iCurrLabel;

        retVal = mOrder.insert(std::make_pair(edge->First(), iCurrLabel));
        if (retVal.second)
            --iCurrLabel;

    });

    return std::move(mOrder);
}

bool DirectedGraph::IsAcyclic() const
{
    int iFirstNode = 1;
    bool bIsCyclic = false;;
    std::vector<int> exploredNodes;

    DFS(iFirstNode, [&bIsCyclic, &exploredNodes](std::shared_ptr<Edge> edge) -> void
    {
        exploredNodes.push_back(edge->First());
        auto direction = edge->Direction();
        if (direction == EdgeDirection::FIRST_TO_SECOND)
        {
            if (std::find(exploredNodes.begin(), exploredNodes.end(), edge->Second()) !=
                std::end(exploredNodes))
            {
                bIsCyclic = true;
            }
        }
    });

    return !bIsCyclic;
}
//TODO: 
// implement check whether graph is acyclic
