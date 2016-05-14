#include "graph.h"
#include <algorithm>

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

}

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
		++m_iVertexNum;
    }
}


