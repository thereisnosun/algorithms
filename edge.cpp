#include "edge.h"

Edge::Edge(int iOne, int iTwo)
{
    m_Edge.first = iOne;
    m_Edge.second = iTwo;
}

/*
m_bFirstLast - boolean var which determins direction
if true - then first node -> second node
if false - then first node <- second node
*/
DirectedEdge::DirectedEdge(int iOne, int iTwo, bool bDirection) :
    Edge(iOne, iTwo), m_bFirstLast(bDirection)
{

}

WeightEdge::WeightEdge(int iOne, int iTwo, int iWeight) :
    Edge(iOne, iTwo), m_iWeight(iWeight)
{

}

DirectedWeightEdge::DirectedWeightEdge(int iOne, int iTwo, bool bDirection, int iWeight) :
    Edge(iOne, iTwo), DirectedEdge(iOne, iTwo, bDirection), WeightEdge(iOne, iTwo, iWeight)
{

}