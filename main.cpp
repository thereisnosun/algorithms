#include <iostream>
#include "algorithms.h"
#include "sort.h"
#include "graph.h"


int main(int argc, char *argv[])
{
	int test[] = { 1, 23,64, 5, 7, 2, 56, 77, 234, 23,5,6,8,9,34,6,6,546,};

	std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));

    //int iSplit = Sort::MergeSort(vVector.begin(), vVector.end());
    //std::cout << "Split inversions - " << iSplit << std::endl;

    /*Sort::QuickSort(vVector.begin(), vVector.end());

	Algo::PrintContainer(vVector.begin(), vVector.end());
*/

	//TODO: v2012 does not support init list;
#ifdef  _MSC_PLATFORM_TOOLSET_v140
    //Graph graph({ { 0, 1, 0, 0, 1 },
    //              { 1, 0, 1, 0, 1 },
    //              { 0, 1, 0, 1, 1 },
    //              { 0, 0, 1, 0, 1 },
    //              { 1, 1, 1, 1, 0} });
    //auto minimumCut = graph.FindMinimumCut();
    //size_t iMinimumCut = minimumCut.size();
    //std::cout << iMinimumCut;

    Graph graphPath({ {0, 1, 1, 0, 0, 0},
                    {1, 0, 0, 1, 0, 0},
                    {1, 0, 0, 1, 1, 0 },
                    {0, 1, 1, 0, 1, 1 },
                    {0, 0, 1, 1, 0, 1 },
                    {0, 0, 0, 1, 1, 0 }, });
    int iPath = graphPath.FindMinimumPath(2, 4);
    std::cout << iPath;

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

	return 0;
}