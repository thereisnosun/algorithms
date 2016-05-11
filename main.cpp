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

    Sort::QuickSort(vVector.begin(), vVector.end());

	Algo::PrintContainer(vVector.begin(), vVector.end());


    std::vector<int> v1 = { 0, 1, 0 };
    std::vector<int> v2 = { 1, 0, 1 };
    std::vector<int> v3 = { 0, 1, 0 };

    std::vector<std::vector<int>> matrix = { v1, v2, v3 };
    Graph graph(matrix);

	return 0;
}