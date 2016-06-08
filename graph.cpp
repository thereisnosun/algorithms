#include "graph.h"
#include <algorithm>
#include <ctime>
#include <queue>
#include <map>

//TODO: add ability to insert not connected vertexes
Graph::Graph(const std::vector<std::vector<int>> &vAdjMatrix):
    m_iVertexNum(0)
{
	GraphRepresentation repr = CheckRepresentation(vAdjMatrix);
	if (repr == GraphRepresentation::MATRIX)
	{
		BuildFromMatrix(vAdjMatrix);
	}
	else if (repr == GraphRepresentation::VECTOR_LIST)
	{
		BuildFromVectorList(vAdjMatrix);
	}
	else
	{
		//TODO: throw exception
	}
    
}

GraphRepresentation Graph::CheckRepresentation(const std::vector<std::vector<int>> &vAdjMatrix) const
{
	GraphRepresentation graphRepr = GraphRepresentation::MATRIX;
	size_t uMatrixHeight = vAdjMatrix.size();

	for( auto itCurrent = vAdjMatrix.begin(); itCurrent != vAdjMatrix.end(); ++itCurrent)
	{
		if (uMatrixHeight != itCurrent->size())
		{
			graphRepr = GraphRepresentation::VECTOR_LIST;
			break;
		}
	}

	return std::move(graphRepr);
}

//first case
//representation:
//0 1 0
//1 0 1
//0 1 0
void Graph::BuildFromMatrix(const std::vector<std::vector<int>> &vAdjMatrix)
{
    auto itCurrent = vAdjMatrix.begin();
    auto itEnd = vAdjMatrix.end();
    int glVertex = 1;
    for (; itCurrent != itEnd; ++itCurrent)
    {
        auto vAdjVector = *itCurrent;
        auto itAdjCurrent = vAdjVector.begin();
        auto itAdjEnd = vAdjVector.end();
        int lcVertex = 1;
        for (; itAdjCurrent != itAdjEnd; ++itAdjCurrent)
        {
            if (*itAdjCurrent == 1)
            {
                AddUniquePair(glVertex, lcVertex);
            }

            ++lcVertex;
        }

        ++glVertex;
    }
    m_iVertexNum = --glVertex;
}

//second case representation
//2
//1, 3
//2
void Graph::BuildFromVectorList(const std::vector<std::vector<int>> &vAdjMatrix)
{
	auto itCurrent = vAdjMatrix.begin();
	auto itEnd = vAdjMatrix.end();
	int glVertex = 1;
	for (; itCurrent != itEnd; ++itCurrent)
	{
		auto vAdjVector = *itCurrent;
		std::for_each(vAdjVector.begin(), vAdjVector.end(), [this, glVertex](int iVertex)->void
		{
			AddUniquePair(glVertex, iVertex);
		});

		++glVertex;
	}
    m_iVertexNum = --glVertex;
}


void Graph::AddEdge(const std::pair<int, int> &edge)
{
    AddUniquePair(edge.first, edge.second);
}

//represented by the vector of edges, which connected with each other
void Graph::AddVertex(const std::vector<int> &vVertex)
{
    if (vVertex.empty())
        return;

    std::for_each(vVertex.begin(), vVertex.end(), [this](int iVertex)->void
    {
        AddUniquePair(m_iVertexNum + 1, iVertex);
    });

    ++m_iVertexNum;

}

//FIXME: graph CAN have duplicate edges!
void Graph::AddUniquePair(int m, int n)
{
    auto itFind = std::find_if(m_vAdjacencyVector.begin(), m_vAdjacencyVector.end(), 
                               [&m, &n](const std::pair<int, int> &currPair)->bool
    {
        if (currPair.first == m && currPair.second == n)
        {
            return true;
        }
        if (currPair.first == n && currPair.second == m)
        {
            return true;
        }
        return false;
    });

    if (itFind == std::end(m_vAdjacencyVector))
    {
        m_vAdjacencyVector.push_back(std::make_pair(m, n));
    }
}

//this is just krager algorithm, so it is not necesserely find a minimum cut
//TODO: test this function carefully
size_t Graph::FindMinimumCut() const
{
    std::vector<std::pair<int, int>> vMinimumCut(m_vAdjacencyVector.size());
    
    std::copy(m_vAdjacencyVector.begin(), m_vAdjacencyVector.end(), vMinimumCut.begin());
    int iVertexs = m_iVertexNum;

    std::srand(static_cast<unsigned int>(std::time(0))); 
    while (iVertexs > 2)
    {
        int iRand = std::rand() % vMinimumCut.size();
        auto edge = vMinimumCut.at(iRand);
        
        vMinimumCut.erase(vMinimumCut.begin() + iRand);
        int deleteVertex = iRand % 2 == 0 ? edge.first : edge.second;
        int leftVertex = iRand % 2 == 0 ? edge.second : edge.first;

        std::for_each(vMinimumCut.begin(), vMinimumCut.end(), [&deleteVertex, &leftVertex](std::pair<int, int> &currentEdge)->void
        {
            if (deleteVertex == currentEdge.first)
            {
                currentEdge.first = leftVertex;
            }

            if (deleteVertex == currentEdge.second)
            {
                currentEdge.second = leftVertex;
            }
                
        });
     
        --iVertexs;
    }

    auto itNewEndr = std::remove_if(vMinimumCut.begin(), vMinimumCut.end(), [&vMinimumCut](const std::pair<int, int> &currentEdge)->bool
    {
        if (currentEdge.first == currentEdge.second)
            return true;
        return false;
    });

    std::vector<std::pair<int, int>> vTrueMinCut(vMinimumCut.begin(), itNewEndr);
    
    //TODO: check if size of the graph was not changes, if it was not return cashed value
    return vTrueMinCut.size();
}

//based on bfs
//TODO: BFS - separate routine, use it for finding minimum path and connected components
int Graph::FindMinimumPath(int iNode1, int iNode2) const
{
    std::queue<int> checkQueue;
    std::vector<int> exploredNodes;
    int iCurrentVertex = iNode1;
    checkQueue.push(iCurrentVertex);
    exploredNodes.push_back(iCurrentVertex);

    std::map<int, int> mDistances;
    mDistances.insert(std::make_pair(iCurrentVertex, 0));
    while (!checkQueue.empty())
    {
        auto currentVertex = checkQueue.front();
        checkQueue.pop();

        for (auto itCurrent = m_vAdjacencyVector.begin(); itCurrent != m_vAdjacencyVector.end(); ++itCurrent)
        {
            int iNewVertex = -1;
            if (itCurrent->first == currentVertex)
            {
                iNewVertex = itCurrent->second;
            }

            if (itCurrent->second == currentVertex)
            {
                iNewVertex = itCurrent->first;
            }

            if (iNewVertex != -1)
            {
                auto itFind = std::find(exploredNodes.begin(), exploredNodes.end(), iNewVertex);
                if (itFind == std::end(exploredNodes))
                {
                    exploredNodes.push_back(iNewVertex);
                    checkQueue.push(iNewVertex);
                    int iCurrDist = mDistances.at(currentVertex);
                    mDistances.insert(std::make_pair(iNewVertex, ++iCurrDist));
                }
               
            }
       
        }
    }

    return mDistances.at(iNode2);
}