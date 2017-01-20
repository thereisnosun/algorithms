#include "best_practises.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

void Item7ObjectConstrutc()
{//NOTE: Braces are uniform. Use braces.
    int x(0);
    int y = 0;
    int z = { 0 };

    TestFeatures f(); //declares a fnction which return TestFeatures
    TestFeatures test{}; //constructs TestFeatures object

    TestFeatures test1{ 10, true };
    TestFeatures test2{ 10, 7.7 };
    TestFeatures test3(test1);
    TestFeatures test4{ test1 };
    TestFeatures test5(std::move(test2));
    TestFeatures test6{ std::move(test2) };

    std::vector<int> vVec{ 1,3,5 }; // use std::initializer_list 3 elements - 1, 3, 5
    std::vector<int> vVecBig(10, 7); // create 10 elements with value 7
}


template<typename T>
using MyAllocVector = std::vector<T, TestAllocator<T>>;
//typedef analogue:
template <typename T>
struct MyAllocVectorDef
{
    typedef std::vector<T, TestAllocator<T>> type;
};


void Item9AliasDeclaration()
{//NOTE: use type aliases, not typedef
    using StrVector = std::vector < std::string > ;
    using UPtrStrVector = std::unique_ptr<StrVector>;

    const auto vBands = UPtrStrVector{ new StrVector{"Elf", "Dio", "Queen"} };

    typedef void(*fp)();
    using fp_alias = void(*)();

    MyAllocVector<int> vVectorAlloc;
    MyAllocVectorDef<int>::type vVectorAllocDef;
    
    
}