#include <iostream>

#include "algorithms.h"

int main(int argc, char *argv[])
{
	int test[] = { 1, 23,64,5,7 };

	std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));

	int iSplit = Algo::MergeSort(vVector.begin(), vVector.end());
	std::cout << "Split inversions - " << iSplit << std::endl;
	Algo::PrintContainer(vVector.begin(), vVector.end());

	return 0;
}