#include <iostream>

#include "algorithms.h"

int main(int argc, char *argv[])
{
	int test[] = { 1, 23, 89, 7, 8, 45 };
	//Algo::MergeSort(test, 0, 5);
	//Algo::PrintArray(test, 5);

	std::vector<int> vVector(test, test + sizeof(test) / sizeof(int));

	Algo::MergeSort(vVector.begin(), vVector.end());
	//Algo::PrintVector(vVector);
	Algo::PrintContainer(vVector.begin(), vVector.end());

	/*std::shared_ptr <std::vector<int>> pSortedVector = Algo::MergeSort(vVector);
	Algo::PrintVector(*pSortedVector);*/
	//std::cout << Algo::GetContainerLen(pSortedVector->begin(), pSortedVector->end());
	return 0;
}