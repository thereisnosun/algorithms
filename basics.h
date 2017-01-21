#pragma once

#include <vector>
#include <type_traits>
#include <memory>

template <typename T>
constexpr bool Default_constructible()
{
	return std::is_default_constructible<T>::value;
}

template <typename T>
constexpr bool Destructible()
{
	return std::is_destructible<T>::value;
}

template <typename T>
constexpr bool Move_constructible()
{
	return std::is_move_constructible<T>::value;
}

template <typename T>
constexpr bool Move_assignable()
{
	return std::is_move_assignable<T>::value;
}

template <typename T>
constexpr bool Copy_constructible()
{
	return std::is_copy_constructible<T>::value;
}

template <typename T>
constexpr bool Copy_assignable()
{
	return std::is_copy_assignable<T>::value;
}

template<typename T>
constexpr bool Semiregular()
{
	return Destructible<T>()
		&& Default_constructible<T>()
		&& Move_constructible<T>()
		&& Move_assignable<T>()
		&& Copy_constructible<T>()
		&& Copy_assignable<T>();
}

template<typename T>
struct On_heap {
	On_heap() :p(new T) { } // allocate
	~On_heap() { delete p; } // deallocate
	T& operator*() { return *p; }
	T* operator->() { return p; }
	On_heap(const On_heap&) = delete; // prevent copying
	On_heap operator=(const On_heap&) = delete;
private:
	T* p; // pointer to object on the free store
};
template<typename T>
struct Scoped {
	T& operator*() { return x; }
	T* operator->() { return &x; }
	Scoped(const Scoped&) = delete; // prevent copying
	Scoped operator=(const Scoped&) = delete;
private:
	T x; // the object
};
constexpr int on_stack_max = 1024;

template<typename T>
struct Obj_holder {
	using type = typename std::conditional<(sizeof(T) <= on_stack_max),
		Scoped<T>, // first alternative
		On_heap<T> // second alternative
	>::type;
};

template <bool B, typename T, typename F>
using Conditional = typename std::conditional<B, T, F>::type;

template <typename T>
using ValueType = typename std::iterator_traits<T>::value_type;

template <typename T>
using DifferenceType = typename std::iterator_traits<T>::difference_type;

template <bool B, typename T>
using Enable_If = typename std::enable_if<B, T>::type;


template <typename T>
bool IsClass()
{
	return std::is_class<T>::value;
}
