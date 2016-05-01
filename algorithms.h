#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

namespace Algo
{
   

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