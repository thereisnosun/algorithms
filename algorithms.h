#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

namespace Algo
{
   
	

	//TODO: add ability to piggybacking by calling some custom function
	//TODO: closest split pair
	//template <class T>
	//using VectorPair = std::vector<std::pair<typename T::value_type, typename T::value_type>>;
	// is this only VS2015 compilable?

	//template <class T>
	//VectorPair<T> FindClosestPair(T &first, T &last)
	//{

	//	return nullptr;
	//}

 
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
	void PrintContainer(const T &first, const T &last, const std::string &sSeparator = " ")
	{
		std::copy(first, last, std::ostream_iterator<typename T::value_type>(std::cout, sSeparator.c_str()));
	}
}