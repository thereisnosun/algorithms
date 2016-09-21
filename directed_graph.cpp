#include "algorithms.h"
#include "directed_graph.h"

#include <algorithm>


bool operator==(const NodeFinish &comparedNode1, const NodeFinish &comparedNode2)
{
    return comparedNode1.m_iNode == comparedNode2.m_iNode;
}

bool operator==(const NodeFinish &comparedNode1, int iNode)
{
    return comparedNode1.m_iNode == iNode;
}
bool operator<(const NodeFinish &comparedNode1, const NodeFinish &comparedNode2)
{
    return comparedNode1.m_iProcessedOrder > comparedNode2.m_iProcessedOrder;
}

//finish times relation is
//node processing finish
//9 -> 1          6 
//6 -> 2          5
//8 -> 4          4
//2 -> 5          3
//3 -> 6          2
//5 -> 3          1

const std::vector<DirectedGraph>& DirectedGraph::ComputeSCC() 
{
    //TODO:
    //1. Reverse directed graph
    //2. run DFS on Grev(go backwards, instead of copying whole graph).finishing time
    //3. run DFS on original graph process nodes in decreasing order of finishing times
    int iStartNode = m_iNumVertex; //starting from very last node
    std::map<int, int> mFinishTimes;
    std::set<NodeFinish> vExploredNodes;

    int iProcessedOrder = 1;
    int iLeadNode = iStartNode;
    int iFinishCounter = 1;
    do
    {
        std::set<int> vCloseVertexs;
        DFS(iStartNode, [&](std::shared_ptr<Edge> edge,
            /*node to which we are going*/int iCurrNode) -> bool
        {
            EdgeDirection direction = edge->Direction();

            bool bIsAllowed = false;
            if (direction == EdgeDirection::FIRST_TO_SECOND)
            {
                if (edge->First() == iCurrNode)
                {//reverse order
                    bIsAllowed = true;
                }
            }
            else
            {
                if (edge->Second() == iCurrNode)
                {//reverse order
                    bIsAllowed = true;
                }
            }

            int iExploringNode = edge->First() == iCurrNode ? edge->Second() : edge->First();
            if (iLeadNode != iExploringNode)
            {
                NodeFinish processed(iLeadNode, iProcessedOrder);
                iProcessedOrder = CheckFinishTime(vCloseVertexs, vExploredNodes, processed, mFinishTimes, iFinishCounter);
                iLeadNode = iExploringNode;
            }
            if (bIsAllowed)
                vCloseVertexs.insert(iCurrNode);

            return bIsAllowed;
        });
        
        NodeFinish processed(iLeadNode, iProcessedOrder);
        iProcessedOrder = CheckFinishTime(vCloseVertexs, vExploredNodes, processed, mFinishTimes, iFinishCounter);
        std::for_each(vExploredNodes.begin(), vExploredNodes.end(), 
                      [&] (const NodeFinish &node) -> void
        {
            if (mFinishTimes.find(node.m_iNode) == std::end(mFinishTimes))
            {
                mFinishTimes.insert(std::make_pair(node.m_iNode, iFinishCounter++));
            }
        });

        auto itFind = std::end(vExploredNodes);
        do
        {
            --iStartNode;
            itFind = std::find(vExploredNodes.begin(), vExploredNodes.end(), iStartNode);
        } while (itFind != std::end(vExploredNodes));

    } while (iStartNode > 0);

    Algo::PrintMap(mFinishTimes);


    


    return m_vSCC;
}

//TODO: define allias for custom find_if

bool DirectedGraph::IsNodeExplored(const std::set<NodeFinish> &vExploredNodes, int iNode) const
{
    auto itFind = std::find_if(vExploredNodes.begin(), vExploredNodes.end(), [iNode](const NodeFinish &node)->bool
    {
        return iNode == node.m_iNode;
    });

    return itFind != std::end(vExploredNodes);
}

//TODO: refactor this function
int DirectedGraph::CheckFinishTime(std::set<int> &vCloseVertexs, std::set<NodeFinish> &vExploredNodes, const NodeFinish &processed,
                                    std::map<int, int> &mFinishTimes, int &iFinishCounter) const
{
    bool bIsMoreVertex = false;


    std::for_each(vCloseVertexs.begin(), vCloseVertexs.end(), 
                  [&bIsMoreVertex, &vExploredNodes, this](int iVertex) -> void
    {
    
        if (!IsNodeExplored(vExploredNodes, iVertex))
        {
            bIsMoreVertex = true;
        }
    });

    int iProcessedOrder = processed.m_iProcessedOrder;
    if (vExploredNodes.insert(processed).second)
        ++iProcessedOrder;

    if (!bIsMoreVertex)
    {
        auto itFind = std::find(vExploredNodes.begin(), vExploredNodes.end(), processed);
        if (IsNodeExplored(vExploredNodes, processed.m_iNode))
        {
            if (mFinishTimes.find(processed.m_iNode) == std::end(mFinishTimes))
            {
                std::cout << "Inserting... " << processed.m_iNode << "=" << iFinishCounter << "\n";
                mFinishTimes.insert(std::make_pair(processed.m_iNode, iFinishCounter));
                ++iFinishCounter;
            }
        }
    }

    vCloseVertexs.clear();
    return iProcessedOrder;
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
            if (edge->Second() == iCurrNode)
            {//normal order
                bIsAllowed = true;
            }
        }
        else
        {
            if (edge->First() == iCurrNode)
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
