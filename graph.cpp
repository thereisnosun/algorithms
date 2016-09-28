#include "graph.h"
#include "algorithms.h"

#include <algorithm>
#include <ctime>
#include <queue>
#include <stack>
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
                AddUniqueEdge(new Edge(lcVertex, glVertex));
            }
            ++lcVertex;
        });
        ++glVertex;
    });
    m_iNumVertex = --glVertex;
}


void Graph::AddEdge(Edge *edge)
{
    AddUniqueEdge(edge); 
}

void Graph::AddEdge(int iVert1, int Vert2)
{
    AddUniqueEdge(new Edge(iVert1, Vert2));
}

void Graph::AddVertex(const std::vector<int> &vAdjency)
{
    if (vAdjency.empty())
        return;

    std::for_each(vAdjency.begin(), vAdjency.end(), [this](int iVertex)->void
    {
        AddUniqueEdge(new Edge(m_iNumVertex + 1, iVertex));
    });
}

void Graph::AddUniqueEdge(Edge *edge)
{
    auto itFind = std::find_if(m_vEdges.begin(), m_vEdges.end(),
                               [&edge](const std::shared_ptr<Edge> &currEdge)->bool
    {
        if (currEdge->First() == edge->First() && currEdge->Second() == edge->Second())
        {
            return true;
        }
        if (currEdge->First() == edge->Second() && currEdge->Second() == edge->First())
        {
            return true;
        }
        return false;
    });

    if (itFind == std::end(m_vEdges))
    {
        //TODO: check for memory leak
        m_sVertex.insert(edge->Second());
        m_sVertex.insert(edge->First());
        m_iNumVertex = static_cast<int>(m_sVertex.size());
        m_vEdges.push_back(std::make_shared<Edge>(*edge));
    
    }
    else
    {
        delete edge;
        edge = nullptr;
    }
}

void Graph::AddUniqueVertex(int iNode)
{
    
}

//TODO: check if size of the graph was not changed, if it was not return cashed value
//TODO: add ability to add stand-alone nodes(which is not connected between each other)
size_t Graph::FindMinimumCut() const
{
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

bool Graph::IsNodePresent(int iNode) const
{
    return m_sVertex.find(iNode) != std::end(m_sVertex);
}

#include <iostream>

void Graph::DFS(int iNode, std::function<bool(std::shared_ptr<Edge> edge, int iCurrentNode)> workFunc, bool bIsNewSearch) const
{
    std::stack<int> checkStack;
    static std::set<int> markedNodes;

    if (bIsNewSearch)
        markedNodes.clear();

    checkStack.push(iNode);
    markedNodes.insert(iNode);
    std::cout << "Exploring " << iNode << "\n";
    while (!checkStack.empty())
    {
        int iCurrVertex = checkStack.top();
        checkStack.pop();

        auto itRet = markedNodes.insert(iCurrVertex);
        std::cout << "Exploring " << iCurrVertex << "\n";
        for (auto itCurr = m_vEdges.begin(); itCurr != m_vEdges.end(); ++itCurr)
        {
            auto curEdge = *itCurr;
            int iNewVertex = -1;
            if (curEdge->First() == iCurrVertex)
            {
                iNewVertex = curEdge->Second();
            }

            if (curEdge->Second() == iCurrVertex)
            {
                iNewVertex = curEdge->First();
            }
           
            if (iNewVertex != -1)
            {
                auto itFind = std::find(markedNodes.begin(), markedNodes.end(), iNewVertex);
                bool bIsPath = workFunc(curEdge, iNewVertex);
                if (itFind == std::end(markedNodes))
                {
                    if (bIsPath)
                    {
                        checkStack.push(iNewVertex);
                    }
                }
            }

        }

    }
}

//NOTE: can storing neighbours of each edge  help improve productivity ?
//define some template structure which will receive result from the lambdas, (e.g. if graph not-weight then weight edge
//will always be 1, otherwise it could be some arbitrary value) 
//if graph not directed than path will always be walkable, otherwise it will depend on direction

