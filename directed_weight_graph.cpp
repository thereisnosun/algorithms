#include "directed_weight_graph.h"
#include <algorithm>
#include <iterator>
#include <iostream>

PathWeight::PathWeight() :
    m_iLeadNode(0), m_iTotalScore(0)
{

}

PathWeight::PathWeight(int iLeadNode, std::shared_ptr<Edge> pEdge) :
    m_iLeadNode(iLeadNode), m_iTotalScore(pEdge->Weight())
{
    m_vEdges.push_back(pEdge);
}
PathWeight::PathWeight(const PathWeight &weight)
{
    m_iLeadNode = weight.m_iLeadNode;
    m_iTotalScore = weight.m_iTotalScore;
    m_vEdges.reserve(weight.m_vEdges.size());
    std::copy(weight.m_vEdges.begin(), weight.m_vEdges.end(), std::back_inserter(m_vEdges));
}
PathWeight::PathWeight(const PathWeight &&weight)
{
    m_iLeadNode = weight.m_iLeadNode;
    m_iTotalScore = weight.m_iTotalScore;
    m_vEdges = std::move(weight.m_vEdges);
}
PathWeight& PathWeight::operator=(const PathWeight &weight)
{
    if (this == &weight)
        return *this;

    m_iLeadNode = weight.m_iLeadNode;
    m_iTotalScore = weight.m_iTotalScore;
    m_vEdges.clear();
    m_vEdges.reserve(weight.m_vEdges.size());
    std::copy(weight.m_vEdges.begin(), weight.m_vEdges.end(), std::back_inserter(m_vEdges));
    return *this;
}
PathWeight& PathWeight::operator=(const PathWeight &&weight)
{
    if (this == &weight)
        return *this;

    m_iLeadNode = weight.m_iLeadNode;
    m_iTotalScore = weight.m_iTotalScore;
    m_vEdges = std::move(weight.m_vEdges);
}
void PathWeight::AddEdge(int iLeadNode, std::shared_ptr<Edge> pEdge)
{
    m_iLeadNode = iLeadNode;
    m_iTotalScore += pEdge->Weight();
    m_vEdges.push_back(pEdge);
}

bool operator < (const PathWeight &weight1, const PathWeight &weight2)
{
    return weight1.m_iTotalScore > weight2.m_iTotalScore; // for making minimal heap instead of maximal
}


//NOTE: this can actually be put in to the very base class with only method which checks path possibily ovwerriden
PathWeight DirectedWeightGraph::FindShortestPath(int iNode1, int iNode2) const
{
    PathWeight shortestPath;

    std::vector<std::shared_ptr<Edge>> vLocalEdges;
    vLocalEdges.reserve(m_vEdges.size());
    std::copy(m_vEdges.begin(), m_vEdges.end(), std::back_inserter(vLocalEdges));

    bool bIsFirstNode = false;
    bool bIsSecondNode = false;
    std::for_each(vLocalEdges.begin(), vLocalEdges.end(), 
                               [&](const std::shared_ptr<Edge> pEdge) -> void
    {
        if (pEdge->First() == iNode1 || pEdge->Second() == iNode1)
        {
            bIsFirstNode = true;
        }

        if (pEdge->First() == iNode2 || pEdge->Second() == iNode2)
        {
            bIsSecondNode = true;
        }

    });

    if (!bIsFirstNode || !bIsSecondNode)
    {
        std::cout << "Edge is not present in the graph!\n";
        return std::move(shortestPath);
    }

    //TODO: use dequeu instead of vector ?
    std::vector<PathWeight> vPaths;
    std::set<std::shared_ptr<Edge>> sUsedEdges;
    std::make_heap(vPaths.begin(), vPaths.end());
    int iCurrNode = iNode1;
    while (iCurrNode != iNode2)
    {
        for (auto itCurr = vLocalEdges.begin(); itCurr != vLocalEdges.end(); ++itCurr)
        {
            std::shared_ptr<Edge> pCurrEdge = *itCurr;

            if (sUsedEdges.find(pCurrEdge) != std::end(sUsedEdges))
                continue;
            if (pCurrEdge->First() == iCurrNode || pCurrEdge->Second() == iCurrNode)
            {
                int iStartNode = pCurrEdge->First() == iCurrNode ? pCurrEdge->First() : pCurrEdge->Second();
                int iLeadNode = pCurrEdge->First() == iCurrNode ? pCurrEdge->Second() : pCurrEdge->First();
                bool bIfPathExists = IfPathExists(iLeadNode, pCurrEdge);
                if (bIfPathExists)
                {
                    sUsedEdges.insert(pCurrEdge);
                    if (iCurrNode == iNode1)
                    {//first iteration, add all possible nodes
                        PathWeight currWeight(iLeadNode, pCurrEdge);
                        vPaths.push_back(currWeight);
                    }
                    else
                    {
                        std::make_heap(vPaths.begin(), vPaths.end());
                        std::pop_heap(vPaths.begin(), vPaths.end());
                        auto minPath = vPaths.back();
                        minPath.AddEdge(iLeadNode, pCurrEdge);
                        int iLastIndex = vPaths.size() - 1;
                        vPaths[iLastIndex] = minPath;
                    }
                }
            }

        }

        std::pop_heap(vPaths.begin(), vPaths.end());
        auto minPath = vPaths.back();
        iCurrNode = minPath.m_iLeadNode;
    }
     
    return std::move(shortestPath);
}

int DirectedWeightGraph::RegisterEdge(std::vector<PathWeight> &vPaths, const std::shared_ptr<Edge> &pCurrEdge, int iStartNode) const
{
    int iCurrNode = 0;
    int iLeadNode = pCurrEdge->First() == iStartNode ? pCurrEdge->Second() : pCurrEdge->First();
    bool bIfPathExists = IfPathExists(iLeadNode, pCurrEdge);
    if (bIfPathExists)
    {
        if (!vPaths.empty())
        {
            std::pop_heap(vPaths.begin(), vPaths.end());
            auto minPath = vPaths.back();
            iCurrNode = minPath.m_iLeadNode;
            minPath.AddEdge(iStartNode, pCurrEdge);
            //int iIndex = vPaths.size() - 1;
            //vPaths[iIndex] = minPath;
        }
        else
        {
            PathWeight currWeight(iStartNode, pCurrEdge);
            vPaths.push_back(currWeight);
            iCurrNode = iLeadNode;
        }
    }

    return iCurrNode;
}

bool DirectedWeightGraph::IfPathExists(int iLeadNode, std::shared_ptr<Edge> pEdge1) const
{
    if (iLeadNode == pEdge1->First() && pEdge1->Direction() == EdgeDirection::SECOND_TO_FIRST)
    {
        return true;
    }

    if (iLeadNode == pEdge1->Second() && pEdge1->Direction() == EdgeDirection::FIRST_TO_SECOND)
    {
        return true;
    }

    return false;
}


