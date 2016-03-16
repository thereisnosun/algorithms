#include <iostream>

#include "algorithms.h"

int main(int argc, char *argv[])
{
	int test[] = { 1, 23, 89, 7, 3 };
	//Algo::MergeSort(test, 0, 5);
	//Algo::PrintArray(test, 5);

	std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));
	
	std::shared_ptr <std::vector<int>> pSortedVector = Algo::MergeSort(vVector);
	Algo::PrintVector(*pSortedVector);
	return 0;
}