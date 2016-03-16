#pragma once
#include <iostream>
#include <memory>
#include <vector>

namespace Algo
{
	template <class T>
	void swap(T &t1, T &t2)
	{
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}

	//TODO: first implement for containers
	template <class Type>
	Type* MergeSort(Type *arr, int iStart, int iEnd)
	{
		if (iEnd == 1 || iEnd <= iStart)
			return arr;

		int iMiddle = iEnd / 2;

		Type *arr1 = MergeSort(arr, iStart, iMiddle);
		Type *arr2 = MergeSort(arr, iMiddle + 1, iEnd);

		return Merge(arr1, iStart, iMiddle, arr2, iMiddle + 1, iEnd);
	}

	//template <class Type>
	//Type* Merge(Type *arr1, int iStart1, int iEnd1, Type *arr2, int iStart2, int iEnd2)
	//{
	//	Type *result = new Type[iEnd2];
	//	int i = iStart1;
	//	int j = iStart2;
	//	for (int k = 0; k < iEnd2; ++k)
	//	{
	//		if (arr1[i] < arr2[j])
	//		{
	//			result[k] = arr1[j];
	//			++j;
	//		}
	//		else
	//		{
	//			result[k] = arr2[i];
	//			++i;
	//		}
	//	}
	//	return result;
	//}


	template <class Type>
	std::shared_ptr<std::vector<Type>> MergeSort(std::vector<Type> &vVector)
	{
		if (vVector.size() == 1)
			return std::make_unique<std::vector<Type>>(vVector);
		//return std::shared_ptr<std::vector<Type>>(vVector);

		int iMiddle = vVector.size() / 2;

		std::vector<Type> vVec1(vVector.begin(), vVector.begin() + iMiddle);
		std::vector<Type> vVec2(vVector.begin() + iMiddle, vVector.end());

		std::shared_ptr<std::vector<Type>> vVector1 = MergeSort(vVec1);
		std::shared_ptr<std::vector<Type>> vVector2 = MergeSort(vVec2);

		return  Merge(vVector1, vVector2);

	}

	//TODO: difference between shared_ptr and unique_ptr
	template <class Type>
	std::shared_ptr<std::vector<Type>> Merge(std::shared_ptr<std::vector<Type>> pVec1, std::shared_ptr<std::vector<Type>> pVec2)
	{
		auto Vec1Curr = pVec1->begin();
		auto Vec1End = pVec1->end();

		auto Vec2Curr = pVec2->begin();
		auto Vec2End = pVec2->end();

		//std::shared_ptr<std::vector<Type>> resVector(new std::vector<Type>);
		std::vector<Type> resVector;
		//resVector.resize(pVec1->size() + pVec2->size());

		while (Vec1Curr != Vec1End && Vec2Curr != Vec2End)
		{
			if (*Vec1Curr > *Vec2Curr)
			{
				resVector.push_back(*Vec1Curr);
				++Vec1Curr;
			}
			else
			{
				resVector.push_back(*Vec2Curr);
				++Vec2Curr;
			}
		}

		auto pLastIter = Vec1Curr == Vec1End ? Vec2Curr : Vec1Curr;
		auto pEndIter = Vec1Curr == Vec1End ? Vec2End : Vec1End;
		for (; pLastIter != pEndIter; ++pLastIter)
		{
			resVector.push_back(*pLastIter);
		}

		return std::make_unique<std::vector<Type>>(resVector);
	}



	template <class Type>
	void PrintVector(const std::vector<Type> &vVector)
	{
		auto pCurr = vVector.begin();
		const auto pEnd = vVector.end();
		for (; pCurr != pEnd; ++pCurr)
		{
			std::cout << *pCurr << " ";
		}
	}

	template <class Type>
	void PrintArray(Type *arr, int iLength)
	{
		for (int i = 0; i < iLength; ++i)
		{
			std::cout << arr[i] << " ";
		}
	}

}