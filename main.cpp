#include <iostream>
#include "algorithms.h"
#include "sort.h"
#include "graph.h"
#include "directed_graph.h"
#include "directed_weight_graph.h"

#include "best_practises.h"

void MinimumCutTest();
void MinimumPathTest();
void TopologicalOrderTest();

void MergeSortTest();
void QuickSortTest();
void SCCTest();
void DijkstraTest();

int main(int argc, char *argv[])
{
    Item7ObjectConstrutc();
	return 0;
}

void DijkstraTest()
{
    DirectedWeightGraph graph;
    graph.AddEdge(new DirectedWeightEdge{ 1, 2, EdgeDirection::FIRST_TO_SECOND, 1 });
    graph.AddEdge(new DirectedWeightEdge{ 1, 3, EdgeDirection::FIRST_TO_SECOND, 4 });
    graph.AddEdge(new DirectedWeightEdge{ 2, 3, EdgeDirection::FIRST_TO_SECOND, 2 });
    graph.AddEdge(new DirectedWeightEdge{ 2, 4, EdgeDirection::FIRST_TO_SECOND, 6 });
    graph.AddEdge(new DirectedWeightEdge{3, 4, EdgeDirection::FIRST_TO_SECOND, 3});
    auto dikstraPath = graph.FindShortestPath(1, 4);
}

void SCCTest()
{
    DirectedGraph directedGraph;
    directedGraph.AddEdge(new DirectedEdge{ 1, 7, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{ 1, 4, EdgeDirection::FIRST_TO_SECOND });
    directedGraph.AddEdge(new DirectedEdge{ 4, 7, EdgeDirection::FIRST_TO_SECOND });
    directedGraph.AddEdge(new DirectedEdge{7, 9, EdgeDirection::SECOND_TO_FIRST});
    directedGraph.AddEdge(new DirectedEdge{ 9, 6, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{ 5, 9, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{8, 3, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{3, 2, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{2, 8, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{ 6, 8, EdgeDirection::SECOND_TO_FIRST });
    directedGraph.AddEdge(new DirectedEdge{ 6, 5, EdgeDirection::SECOND_TO_FIRST });
    auto compSCC = directedGraph.ComputeSCC();

}

void TopologicalOrderTest()
{
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    DirectedGraph directedGraph;
    directedGraph.AddEdge(new DirectedEdge{1, 2, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{1, 3, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{2, 4, EdgeDirection::FIRST_TO_SECOND});
    directedGraph.AddEdge(new DirectedEdge{3, 4, EdgeDirection::FIRST_TO_SECOND});
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
    graphPath.AddEdge(new Edge(1, 2));
    graphPath.AddEdge(new Edge(1, 3));
    graphPath.AddEdge(new Edge(2, 4));
    graphPath.AddEdge(new Edge(3, 4));
    graphPath.AddEdge(new Edge(3, 5));
    graphPath.AddEdge(new Edge(4, 5));
    graphPath.AddEdge(new Edge(4, 6));
    graphPath.AddEdge(new Edge(5, 6));
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