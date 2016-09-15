#pragma once
#include "graph.h"

struct NodeFinish
{
    int m_iNode;
    int m_iProcessedOrder;
    NodeFinish(int iNode, int iProcessedOrder) :
        m_iNode(iNode), m_iProcessedOrder(iProcessedOrder)
    {

    }
    friend bool operator<(const NodeFinish &comparedNode1, const NodeFinish &comparedNode2);
    friend bool operator==(const NodeFinish &comparedNode1, const NodeFinish &comparedNode2);
    friend bool operator==(const NodeFinish &comparedNode1, int iNode);
};


class DirectedGraph : public Graph
{
public:
    std::map<int, int> TopologicalOrder() const;
    const std::vector<DirectedGraph>& ComputeSCC();
    bool IsAcyclic() const;
private:
    int CheckFinishTime(std::set<int> &vCloseVertexs, std::set<NodeFinish> &vExploredNodes, const NodeFinish &processed,
                         std::map<int, int> &mFinishTimes) const;
private:
    std::vector<DirectedGraph> m_vSCC;
};

