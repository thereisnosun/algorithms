#pragma once
#include <iostream>
#include <initializer_list>
#include <memory>

class TestFeatures
{
public:
    TestFeatures(const TestFeatures &test)
    {
        std::cout << "Copy TestFeatures(const TestFeatures &test) called!\n";
    }
    TestFeatures(const TestFeatures &&test)
    {
        std::cout << "Move TestFeatures(const TestFeatures &&test) called!\n";
    }
    TestFeatures()
    {
        std::cout << "TestFeatures() called!\n";
    }
    TestFeatures(int i, bool b)
    {
        std::cout << "TestFeatures(int i=" <<i << ", bool b=" << b <<") called!\n";
    }
    TestFeatures(int i, double d)
    {
        std::cout << "TestFeatures(int i=" << i << ", double d=" << d << ") called!\n";
    }
    TestFeatures(std::initializer_list<long double> ilist)
    {
        std::cout << "TestFeatures(std::initializer_list<long double> ilist called!\n";
    }
    operator float() const
    {
        std::cout << "TestFeatures::operator float() const called!";
        return 1.0;
    }
};

template <typename T>
class TestAllocator 
{ //TODO: implement
public:
    typedef T value_type;
    TestAllocator(/*ctor args*/)
    {

    }
    template <class U> TestAllocator(const TestAllocator<U>& other)
    {

    }
    T* allocate(std::size_t n)
    {
        return new T;
    };
    void deallocate(T* p, std::size_t n)
    {
        //TODO: implement
    }
};


void Item7ObjectConstrutc();
void Item9AliasDeclaration();