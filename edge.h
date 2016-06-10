#pragma once
#include <map>

//TODO: vertex and edge should have each one classes in order to satisty whole class hierarchy polymorphic behaviour
//edges shall be adopted according to graph

class Edge
{
public:
    Edge(int iOne, int iSecond);
    int First() const
    {
        return m_Edge.first;
    }
    int Second() const
    {
        return m_Edge.second;
    }
    void SetFirst(int iOne)
    {
        m_Edge.first = iOne;
    }
    void SetSecond(int iTwo)
    {
        m_Edge.second = iTwo;
    }
    bool IsSelfLoop() const
    {
        return m_Edge.first == m_Edge.second;
    }
private:
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
    int Weight() const
    {
        return m_iWeight;
    }
private:
    int m_iWeight;
};

class DirectedWeightEdge: public DirectedEdge, public WeightEdge
{
public:
    DirectedWeightEdge(int iOne, int iTwo, bool bDirection, int iWeight);
};