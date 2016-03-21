#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

namespace Algo
{
	template <class Type>
	std::shared_ptr<std::vector<Type>> MergeSort(std::vector<Type> &vVector)
	{
		if (vVector.size() == 1)
			return std::make_shared<std::vector<Type>>(vVector);

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

		std::vector<Type> resVector;

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

		
		return std::make_shared<std::vector<Type>>(resVector);
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

	template <class T>
	void InsertionSort(T &first, T &last)
	{
		for (auto current = first; first != last; ++current)
			std::rotate(std::upper_bound(first, current *current), current, std::next(current));
	}

	template <class T>
	void PrintContainer(const T &first, const T &last)
	{
		std::copy(first, last, std::ostream_iterator<typename T::value_type>(std::cout, " "));
	}

	template <class T>
	int MergeSort(T &first, T &last)
	{
		size_t uSize = std::distance(first, last);
		if (uSize == 1)
			return 0;

		size_t uMiddle = uSize / 2;
		T midIter = std::next(first, uMiddle);
		int firstHalf = MergeSort(first, midIter);
		int secondHalf = MergeSort(midIter, last);

		int iSplitInversion = 0;
		auto vRes = Merge(first, midIter, last, iSplitInversion);
		std::move(vRes.begin(), vRes.end(), first);

		return (iSplitInversion + firstHalf + secondHalf);
	}

	template <class T>
	std::vector<typename T::value_type> Merge(T &first, T& midIter, T &last, int &iSplitInversion)
	{
		T start1 = first;
		T end1 = midIter;
		T start2 = end1;
		T end2 = last;

		std::vector<typename T::value_type> vRes;
		vRes.reserve(std::distance(first, last));
		auto midElement = *midIter;
		while (start1 != end1 && start2 != end2)
		{
			if (*start1 <= *start2)
			{
				vRes.push_back(*start1);
				++start1;
			}
			else
			{
				vRes.push_back(*start2);
				iSplitInversion += std::distance(start1, end1);
				++start2;
			}
		}

		T pLastIter = start1 == end1 ? start2 : start1;
		T pEndIter = start1 == end1 ? end2 : end1;

		for (; pLastIter != pEndIter; ++pLastIter)
		{
			vRes.push_back(*pLastIter);
		}

		return std::move(vRes);
	}


}