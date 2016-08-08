#include "directed_graph.h"



const std::vector<DirectedGraph>& DirectedGraph::ComputeSCC() 
{

    //TODO:
        //1. Reverse directed graph
        //2. run DFS on Grev(go backwards, instead of copying whole graph).
        // finishing time
        //3. run DFS on original graph
        //process nodes in decreasing order of finishing times
    int iStartNode = 1; //assuming we are starting from the very first node
    std::map<int, int> mFinishTimes;
    int iCounter = 1;
    DFS(iStartNode, [&mFinishTimes](std::shared_ptr<Edge> edge, int iCurrNode) -> bool
    {
        EdgeDirection direction = edge->Direction();

        bool bIsAllowed = false;
        if (direction == EdgeDirection::FIRST_TO_SECOND)
        {
            if (edge->Second() == iCurrNode)
            {//reverse order
                bIsAllowed = true;
            }
        }
        else
        {
            if (edge->First() == iCurrNode)
            {//reverse order
                bIsAllowed = true;
            }
        }


        return bIsAllowed;

    });

    return m_vSCC;
}

//TODO: there is a bug here
std::map<int, int> DirectedGraph::TopologicalOrder() const
{
    std::map<int, int> mOrder;

    //find sink vertix, vertix which has not outgoing arcs
    //direction should be taken to consideration
    int iFirstNode = m_iNumVertex; //currently assuming first node equals 1;
    int iCurrLabel = m_iNumVertex;
    DFS(iFirstNode, [&mOrder, &iCurrLabel](std::shared_ptr<Edge> edge, int iCurrNode) -> bool
    {
        EdgeDirection direction = edge->Direction();
        bool bIsAllowed = false;
        if (direction == EdgeDirection::FIRST_TO_SECOND)
        {
            if (edge->First() == iCurrNode)
            {//normal order
                bIsAllowed = true;
            }
        }
        else
        {
            if (edge->Second() == iCurrNode)
            {//normal order
                bIsAllowed = true;
            }
        }

        std::pair<std::map<int, int>::iterator, bool> retVal;
        retVal = mOrder.insert(std::make_pair(edge->Second(), iCurrLabel));
        if (retVal.second)
            --iCurrLabel;

        retVal = mOrder.insert(std::make_pair(edge->First(), iCurrLabel));
        if (retVal.second)
            --iCurrLabel;

        return bIsAllowed;

    });

    return std::move(mOrder);
}

bool DirectedGraph::IsAcyclic() const
{
    int iFirstNode = 1;
    bool bIsCyclic = false;;
    std::vector<int> exploredNodes;

    DFS(iFirstNode, [&bIsCyclic, &exploredNodes](std::shared_ptr<Edge> edge, int iCurrNode) -> bool
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
        return true;
    });

    return !bIsCyclic;
}
