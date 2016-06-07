#pragma once
#include <map>

//TODO: vertex and edge should have each one classes in order to satisty whole class hierarchy polymorphic behaviour
//edges shall be adopted according to graph

class Edge
{
public:
    Edge(int iOne, int iSecond);
protected:
    std::pair<int, int> m_Edge;
};

class DirectedEdge: virtual public Edge
{
public:
    DirectedEdge(int iFirst, int iSecond, bool bDirection);
protected:
    bool m_bFirstLast;
};

class WeightEdge: virtual  public Edge
{
public:
    WeightEdge(int iFirst, int iSecond, int iWeight);
protected:
    int m_iWeight;
};

class DirectedWeightEdge: public DirectedEdge, public WeightEdge
{
public:
    DirectedWeightEdge(int iOne, int iTwo, bool bDirection, int iWeight);
};