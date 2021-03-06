#pragma once
#include <memory>
#include <vector>
#include <iterator>
#include <functional>

namespace Sort
{
    template <class T>
    void InsertionSort(T &first, T &last)
    {
        for (auto current = first; first != last; ++current)
            std::rotate(std::upper_bound(first, current *current), current, std::next(current));
    }

    template <class T>
    void QuickSort(T &first, T &last)
    {
        T oldFirst = first;
        T invalidIt = last;
        Implementation::QuickSort(first, last, 0, static_cast<int>(std::distance(first, last) - 1), oldFirst, invalidIt);
    }

    template <class T>
    void QuickSort(T &first, T &last, std::function<bool(const typename T::value_type &first, const typename T::value_type &second)> comparator)
    {

    }

	template <class Type>
    std::unique_ptr<std::vector<Type>> MergeSort(std::vector<Type> &vVector)
    {
		if (vVector.size() == 1)
		{
#if _MSC_PLATFORM_TOOLSET_v140
			return std::move(std::make_unique<std::vector<Type>>(vVector));
#else
			std::unique_ptr<std::vector<Type>> vVectorPtr;//(new std::vector<Type>());
			vVectorPtr.reset(&vVector);
			return std::move(vVectorPtr);
#endif
			
		}

            

        int iMiddle = static_cast<int>(vVector.size() / 2);

        std::vector<Type> vVec1(vVector.begin(), vVector.begin() + iMiddle);
        std::vector<Type> vVec2(vVector.begin() + iMiddle, vVector.end());

        std::unique_ptr<std::vector<Type>> vVector1 = MergeSort(vVec1);
        std::unique_ptr<std::vector<Type>> vVector2 = MergeSort(vVec2);

        return  std::move(Implementation::Merge(std::move(vVector1), std::move(vVector2)));

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
		auto vRes = Implementation::Merge(first, midIter, last, iSplitInversion);
		std::move(vRes.begin(), vRes.end(), first);

		return (iSplitInversion + firstHalf + secondHalf);
	}

	

    class Implementation
    {
    public:
        template <class T> friend int MergeSort(T &first, T &last);
        template <class Type> friend std::unique_ptr<std::vector<Type>> MergeSort(std::vector<Type> &vVector);
        template <class T> friend void QuickSort(T &first, T &last);
    private:
        template <class T>
        static std::vector<typename T::value_type> Merge(T &first, T& midIter, T &last, int &iSplitInversion)
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
                    iSplitInversion += static_cast<int>(std::distance(start1, end1));
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

        template <class Type>
        static std::unique_ptr<std::vector<Type>> Merge(std::unique_ptr<std::vector<Type>> pVec1, std::unique_ptr<std::vector<Type>> pVec2)
        {
            auto Vec1Curr = pVec1->begin();
            auto Vec1End = pVec1->end();

            auto Vec2Curr = pVec2->begin();
            auto Vec2End = pVec2->end();

            std::unique_ptr<std::vector<Type>> resVector(new std::vector<Type>);

            while (Vec1Curr != Vec1End && Vec2Curr != Vec2End)
            {
                if (*Vec1Curr > *Vec2Curr)
                {
                    resVector->push_back(*Vec1Curr);
                    ++Vec1Curr;
                }
                else
                {
                    resVector->push_back(*Vec2Curr);
                    ++Vec2Curr;
                }
            }

            auto pLastIter = Vec1Curr == Vec1End ? Vec2Curr : Vec1Curr;
            auto pEndIter = Vec1Curr == Vec1End ? Vec2End : Vec1End;
            for (; pLastIter != pEndIter; ++pLastIter)
            {
                resVector->push_back(*pLastIter);
            }


            return std::move(resVector);
        }

        template <class T>
        static void QuickSort(T &first, T &last, int left, int right, T oldFirst, T invalidIt)
        {
            int uMiddle = (right + left) / 2;
            T pivot = std::next(oldFirst, uMiddle);
            typename T::value_type realPivot = *pivot;


            int i = left, j = right;
            if (last == invalidIt)
                --last;

            while (i <= j)
            {
                while (*first < realPivot)
                {
                    ++first;
                    ++i;
                }
                while (*last > realPivot)
                {
                    --last;
                    --j;
                }
                if (i <= j)
                {
                    std::swap(*first, *last);
                    ++i;
                    --j;
                    ++first;
                    if (j >= 0)
                        --last;
                }
            }

            if (left < j)
            {
                QuickSort(std::next(oldFirst, left), std::next(oldFirst, j), left, j, oldFirst, invalidIt);
            } 
            if (i < right)
            {
                QuickSort(std::next(oldFirst, i), std::next(oldFirst, right), i, right, oldFirst, invalidIt);
            }

        }

    };
}