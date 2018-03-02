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
        std::cout << "TestFeatures::operator float() const called!\n";
        return 1.0;
    }
    void DoWork() & //this function called only when *this is lvalue
    {
        std::cout << "TestFeatures::DoWork for l-value called!\n";
    }
    void DoWork() && // this function is called only when *this is an rvalue
    {
        std::cout << "TestFeatures::Dowrk for r-value called!\n";
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
void Item20WeakPtr();
void Item21CreateSmartPtr();
 
template <typename Container, typename Value>
void FindAndInsert(Container &cont, Value &valFind, Value &valIns)
{
    using std::cbegin;
    using std::cend;

    auto itFind = std::find(cbegind(cont), cend(cont), valFind);
    container.insert(itFind, valIns);
}

constexpr
int pow(int base, int exp) noexcept
{
    return (exp == 0 ? 1 : base * pow(base, exp - 1));
}

class ConstructSharedFrom : public std::enable_shared_from_this<ConstructSharedFrom>
{
public:
    void Construct()
    {
        //std::shared now can be constructed from *this pointer
        shared_from_this();
    }
};


//The Curiously Recurring Template Pattern
template <typename T>
class Base
{
public:
    void Interface()
    {
        static_cast<*T>(this)->Function1();
    }
};

class Derived : public Base<Derived>
{
public: 
    void Function1()
    {
        std::cout << "Derived::Function1 is called!\n";
    }
};

template <class T>
struct IsPointer
{
    enum { value = false };
};

template <class T>
struct IsPointer<T*>
{
    enum { value = true };
};