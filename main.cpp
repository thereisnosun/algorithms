#include <iostream>
#include "algorithms.h"
#include "sort.h"
#include "graph.h"

void MinimumCutTest();
void MinimumPathTest();
void MergeSortTest();
void QuickSortTest();

int main(int argc, char *argv[])
{
    MinimumCutTest();

	return 0;
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
    int iPath = graphPath.FindMinimumPath(2, 4);
    std::cout << iPath;
#else
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
    int line1[] = { 0, 1, 0 };
    int line2[] = { 1, 0, 1 };
    int line3[] = { 0, 1, 0 };
    /*      { 0, 1, 0 },
    { 1, 0, 1 },
    { 0, 1, 0 }
    */
    //TODO: support initializer list
#endif
}