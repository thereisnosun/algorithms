#include <algorithm>
#include <ctime>
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
                AddUniquePair(lcVertex, glVertex);
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

void NGraph::AddUniquePair(int m, int n)
{
    auto itFind = std::find_if(m_vEdges.begin(), m_vEdges.end(),
                               [&m, &n](const std::shared_ptr<Edge> &currEdge)->bool
    {
        if (currEdge->First() == m && currEdge->Second() == n)
        {
            return true;
        }
        if (currEdge->First() == n && currEdge->Second() == m)
        {
            return true;
        }
        return false;
    });

    if (itFind == std::end(m_vEdges))
    {
        std::shared_ptr<Edge> pEdge(new Edge(m, n));
        m_vEdges.push_back(std::move(pEdge));
    }
}

size_t NGraph::FindMinimumCut() const
{
    //TODO: check if size of the graph was not changes, if it was not return cashed value
    int iVertexs = m_iNumVertex;
    std::vector<std::shared_ptr<Edge>> vMinimumCut(m_vEdges.size());
    std::copy(m_vEdges.begin(), m_vEdges.end(), vMinimumCut.begin());
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    while (iVertexs > 2)
    {
        int iRand = std::rand() % vMinimumCut.size();
        auto edge = vMinimumCut.at(iRand);

        vMinimumCut.erase(vMinimumCut.begin() + iRand);
        int deleteVertex = iRand % 2 == 0 ? edge->First() : edge->Second();
        int leftVertex = iRand % 2 == 0 ? edge->Second() : edge->First();

        std::for_each(vMinimumCut.begin(), vMinimumCut.end(), 
                      [&deleteVertex, &leftVertex](std::shared_ptr<Edge> &currentEdge)->void
        {
            if (deleteVertex == currentEdge->First())
            {
                currentEdge->SetFirst(leftVertex);
            }

            if (deleteVertex == currentEdge->Second())
            {
                currentEdge->SetSecond(leftVertex);
            }

        });
        --iVertexs;
    }

    auto itNewEndr = std::remove_if(vMinimumCut.begin(), vMinimumCut.end(), 
                                    [](const std::shared_ptr<Edge> &currentEdge)->bool
    {
        return currentEdge->IsSelfLoop();
    });

    int iMinCut = static_cast<int>(std::distance(vMinimumCut.begin(), itNewEndr));
   
    return iMinCut;
}