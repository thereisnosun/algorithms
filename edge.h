#pragma once
#include <map>

//TODO: vertex and edge should have each one classes in order to satisty whole class hierarchy polymorphic behaviour
//edges shall be adopted according to graph


enum class EdgeDirection
{
    UNDIRECTED  = 1,
    FIRST_TO_SECOND,
    SECOND_TO_FIRST
};

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
    int Weight() const 
    {
        return m_iWeight;
    }
    virtual EdgeDirection Direction() const
    {
        return m_direction;
    }
protected:
    EdgeDirection m_direction;
    int m_iWeight;
private:
    std::pair<int, int> m_Edge;
};

class DirectedEdge: virtual public Edge
{
public:
    DirectedEdge(int iFirst, int iSecond, const EdgeDirection &direction);
};

class WeightEdge: virtual  public Edge
{
public:
    WeightEdge(int iFirst, int iSecond, int iWeight);
   
};

class DirectedWeightEdge: public DirectedEdge, public WeightEdge
{
public:
    DirectedWeightEdge(int iOne, int iTwo, const EdgeDirection &direction, int iWeight);
    friend bool operator<(const DirectedWeightEdge &edge1, const DirectedWeightEdge &edge2);
    friend bool operator==(const DirectedWeightEdge &edge1, const DirectedWeightEdge &edge2);
};