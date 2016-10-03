#include "edge.h"

Edge::Edge(int iOne, int iTwo)
{
    m_Edge.first = iOne;
    m_Edge.second = iTwo;
    m_direction = EdgeDirection::UNDIRECTED;
    m_iWeight = 1;
}

/*
m_bFirstLast - boolean var which determins direction
if true - then first node -> second node
if false - then first node <- second node
*/
DirectedEdge::DirectedEdge(int iOne, int iTwo, const EdgeDirection &direction) :
    Edge(iOne, iTwo)
{
    m_direction = direction;
}

WeightEdge::WeightEdge(int iOne, int iTwo, int iWeight) :
    Edge(iOne, iTwo)
{
    m_iWeight = iWeight;
}

DirectedWeightEdge::DirectedWeightEdge(int iOne, int iTwo, const EdgeDirection &direction, int iWeight) :
    Edge(iOne, iTwo), DirectedEdge(iOne, iTwo, direction), WeightEdge(iOne, iTwo, iWeight)
{

}

bool operator<(const DirectedWeightEdge &edge1, const DirectedWeightEdge &edge2)
{
    return edge1.Weight() < edge2.Weight();
}

bool operator==(const DirectedWeightEdge &edge1, const DirectedWeightEdge &edge2)
{
    return edge1.Weight() == edge2.Weight();
}