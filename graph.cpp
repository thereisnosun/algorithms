#include <algorithm>
#include <ctime>
#include <queue>
#include "graph.h"

//on the current state of implementation lets assume graph can have duplicate edeges
Graph::Graph(const std::vector<std::vector<int>> &vAdjencyMatrix)
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


void Graph::AddEdge(Edge *edge)
{
    AddUniquePair(edge->First(), edge->Second()); //looks ugly
}

void Graph::AddEdge(int iVert1, int Vert2)
{
    AddUniquePair(iVert1, Vert2);
}

void Graph::AddVertex(const std::vector<int> &vAdjency)
{
    if (vAdjency.empty())
        return;

    std::for_each(vAdjency.begin(), vAdjency.end(), [this](int iVertex)->void
    {
        AddUniquePair(m_iNumVertex + 1, iVertex);
    });

    ++m_iNumVertex;
}

void Graph::AddUniquePair(int m, int n)
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

size_t Graph::FindMinimumCut() const
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

int Graph::FindMinimumPath(int iNode1, int iNode2) const
{
    std::map<int, int> mDistances;
    mDistances.insert(std::make_pair(iNode1, 0));
    BFS(iNode1, [&mDistances](int iNode1, int Node2) -> void
    {
        int iCurrDist = mDistances.at(iNode1);
        mDistances.insert(std::make_pair(Node2, ++iCurrDist));
    });

    int  iDistance = mDistances.at(iNode2);
    return iDistance;
}

void Graph::BFS(int iNode, std::function<void(int iNode1, int iNode2)> workFunc) const
{
    std::queue<int> checkQueue;
    std::vector<int> exploredNodes;
    int iCurrentVertex = iNode;
    checkQueue.push(iCurrentVertex);
    exploredNodes.push_back(iCurrentVertex);

    while (!checkQueue.empty())
    {
        auto currentVertex = checkQueue.front();
        checkQueue.pop();

        for (auto itCurrent = m_vEdges.begin(); itCurrent != m_vEdges.end(); ++itCurrent)
        {
            auto curEdge = *itCurrent;
            int iNewVertex = -1;
            if (curEdge->First() == currentVertex)
            {
                iNewVertex = curEdge->Second();
            }

            if (curEdge->Second() == currentVertex)
            {
                iNewVertex = curEdge->First();
            }

            if (iNewVertex != -1)
            {
                auto itFind = std::find(exploredNodes.begin(), exploredNodes.end(), iNewVertex);
                if (itFind == std::end(exploredNodes))
                {
                    exploredNodes.push_back(iNewVertex);
                    checkQueue.push(iNewVertex);
                    workFunc(currentVertex, iNewVertex);
                }
            }

        }
    }
}