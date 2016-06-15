#include <iostream>
#include "algorithms.h"
#include "sort.h"
#include "graph.h"

void MinimumCutTest();
void MinimumPathTest();
void TopologicalOrderTest();

void MergeSortTest();
void QuickSortTest();


int main(int argc, char *argv[])
{
    //MinimumPathTest();
    TopologicalOrderTest();

	return 0;
}

void TopologicalOrderTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    DirectedGraph directedGraph;
    directedGraph.AddEdge(new DirectedEdge(1, 2, true));
    directedGraph.AddEdge(new DirectedEdge(1, 3, true));
    directedGraph.AddEdge(new DirectedEdge(2, 4, true));
    directedGraph.AddEdge(new DirectedEdge(3, 4, true));
    auto topologicOrder = directedGraph.TopologicalOrder();
    Algo::PrintMap(topologicOrder);
#else
#endif
}

void MergeSortTest()
{
    int test[] = { 1, 23,64, 5, 7, 2, 56, 77, 234, 23,5,6,8,9,34,6,6,546, };
    std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));

    std::cout << "First implementation:\n";
    std::unique_ptr<std::vector<int>> vResVector = Sort::MergeSort(vVector);
    Algo::PrintContainer(vResVector->begin(), vResVector->end());
    
    std::cout << "\nSecond implementation:\n";
    int iSplit = Sort::MergeSort(vVector.begin(), vVector.end());
    std::cout << "Split inversions - " << iSplit << std::endl;
    Algo::PrintContainer(vVector.begin(), vVector.end());
}

void QuickSortTest()
{
    int test[] = { 1, 23,64, 5, 7, 2, 56, 77, 234, 23,5,6,8,9,34,6,6,546, };
    std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));
    Sort::QuickSort(vVector.begin(), vVector.end());

    Algo::PrintContainer(vVector.begin(), vVector.end());
   
}

void MinimumPathTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    Graph graphPath({ {0, 1, 1, 0, 0, 0},
                    {1, 0, 0, 1, 0, 0},
                    {1, 0, 0, 1, 1, 0 },
                    {0, 1, 1, 0, 1, 1 },
                    {0, 0, 1, 1, 0, 1 },
                    {0, 0, 0, 1, 1, 0 }, });
    int iPath = graphPath.FindMinimumPath(1, 4);
    std::cout << iPath;
#else
    Graph graphPath;
    graph.AddEdge(new Edge(1, 2));
    graph.AddEdge(new Edge(1, 3));
    graph.AddEdge(new Edge(2, 4));
    graph.AddEdge(new Edge(3, 4));
    graph.AddEdge(new Edge(3, 5));
    graph.AddEdge(new Edge(4, 5));
    graph.AddEdge(new Edge(4, 6));
    graph.AddEdge(new Edge(5, 6));
    int iPath = graphPath.FindMinimumPath(1, 4);
    std::cout << iPath;
#endif
}

void MinimumCutTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    Graph graph({ { 0, 1, 0, 0, 1 },
    { 1, 0, 1, 0, 1 },
    { 0, 1, 0, 1, 1 },
    { 0, 0, 1, 0, 1 },
    { 1, 1, 1, 1, 0 } });
    auto minimumCut = graph.FindMinimumCut();
    std::cout << minimumCut;
#else
    Graph graph;
    graph.AddEdge(new Edge(1, 2));
    graph.AddEdge(new Edge(1, 5));
    graph.AddEdge(new Edge(2, 3));
    graph.AddEdge(new Edge(4, 5));
    graph.AddEdge(new Edge(3, 4));
    graph.AddEdge(new Edge(2, 5));
    auto minimumCut = graph.FindMinimumCut();
    std::cout << minimumCut;
#endif
}