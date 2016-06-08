#include <algorithm>
#include "ngraph.h"

//on the current state of implementation lets assume graph can have duplicate edeges
NGraph::NGraph(const std::vector<std::vector<int>> &vAdjencyMatrix)
{
    int glVertex = 1;
    std::for_each(vAdjencyMatrix.begin(), vAdjencyMatrix.end(),
                  [&glVertex, this](const std::vector<int> &vInVec)->void
    {
        int lcVertex = 1;
        std::for_each(vInVec.begin(), vInVec.end(), [&lcVertex, &glVertex, this](int iVert)->void
        {
            if (iVert == 1)
            {
                std::unique_ptr<Edge> pEdge(new Edge(lcVertex, glVertex));
                m_vEdges.push_back(std::move(pEdge));
            }
            ++lcVertex;
        });
        ++glVertex;
    });
    m_iNumVertex = --glVertex;
}


void NGraph::AddEdge(Edge *edge)
{

}

void NGraph::AddVertex()
{

}

size_t NGraph::FindMinimumCut() const
{
    return 0;
}