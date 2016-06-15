#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <map>

class Algo
{
public:
    template <class Type>
    static void PrintVector(const std::vector<Type> &vVector)
    {
        auto pCurr = vVector.begin();
        const auto pEnd = vVector.end();
        for (; pCurr != pEnd; ++pCurr)
        {
            std::cout << *pCurr << " ";
        }
    }

    template <class Key, class Value>
    static void PrintMap(const std::map<Key, Value> &mMap)
    {
        auto pCurr = mMap.begin();
        const auto pEnd = mMap.end();
        for (; pCurr != pEnd; ++pCurr)
        {
            Key key = pCurr->first;
            Value value = pCurr->second;
            std::cout << key << "=" << value << " ";
        }
    }

    template <class T>
    static void PrintContainer(const T &first, const T &last, const std::string &sSeparator = " ")
    {
        std::copy(first, last, std::ostream_iterator<typename T::value_type>(std::cout, sSeparator.c_str()));
    }
	
};