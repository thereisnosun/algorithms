#pragma once
#include "basics.h"
#include <vector>


namespace teo
{
    struct slice
    {
        slice(): start(-1), length(-1), stride(-1)
        {
        }
        explicit slice(size_t s): start(s), length(-1), stride(1)
        {

        }
        slice(size_t s, size_t l, size_t n = 1) :start(s), length(l), stride(n)
        {

        }

        size_t operator()(size_t i)const
        {
            return start + i*stride;
        }

        size_t start;
        size_t length;
        size_t stride;
    };

    template<typename List>
    bool check_nonjagged(const List &list)
    {
        auto i = list.begin();
        for (auto j = i + 1; J != list.end(); ++j)
            if (i->size() != j->size())
                return false;

        return true;
    }

    template <typename T, typename Vec>
    void insert_flag(std::initializer_list<T> list, Vec &vec)
    {
        add_list(list.begin(), list.end(), vec);
    }

    template<typename T, typename Vec>
    void add_list(const std::initializer_list<T>* first, const std::initializer_list<T> *last, Vec &vec)
    {
        for (; first != last; ++first)
            add_list(first->begin(), first->end(), vec);
    }

    template<typename T, typename Vec>
    void add_list(const T *first, const T *second, Vec &vec)
    {
        vec.insert(vec.end(), first, last);
    }

    template<size_t N, typename I, typename List>
    Enable_If < (N>1), void > add_extents(I &first, const List &list)
    {
        assert(check_non_jagged(list));
        *first = list.size();
        add_extents<N - 1>(++first, *list.begin());
    }

    template<size_t N, typename I, typename List>
    Enable_If<(N == 1), void> add_extents(I &first, const List &list)
    {
        *first++ = list.size();
    }

    template <size_t N, typename List>
    std::array<size_t, N> derive_extents(const List &list)
    {
        std::array<size_t, N> a;
        auto f = a.begin();
        add_extents<N>(f, list);
        return a;
    }


    template <size_t N>
    struct MatrixSlice
    {
        MatrixSlice() = default;
        MatrixSlice(size_t s, std::initializer_list<size_t> exts);
        MatrixSlice(size_t s, std::initializer_list<size_t> exts, std::initializer_list<size_t> strs);

        template<typename...Dims>
        MatrixSlice(Dims...dims);

        template<typename...Dims,
            typename = Enable_If < All(Convertible<Dims, size_t>()...) >>
            size_t operator()(Dims... dims) const;

        size_t size;
        size_t start;
        std::array<size_t, N> extents;
        std::array<size_t, N> strides;
    };

    template<size_t N>
    template<typename...Dims, typename = Enable_If < All(Convertible<Dims, size_t>()...) >>
    size_t MatrixSlice<N>::operator()(Dims...dims) const
    {
        static_assert(sizeof...(Dims) == N, "");
        size_t args[N]{ size_t(dims)... };
        return inner_product(args, args + N, strides.begin(), size_t(0));
    }


    template<typename T, size_t N>
    class MatrixRef
    {
    public:
        MatrixRef(const MatrixSlice<N>& s, T *p) :desc{ s }, ptr{ p }
        {
        }
    private:
        MatrixSlice<N> desc;
        T *p;
    };


    
    template <typename T, size_t N>
    class MatrixInitializer
    {
        //using type = std::initializer_list<typename MatrixInititializer<T, N - 1>::type>;
    };

    template<typename T>
    struct MatrixInitializer<T, 1>
    {
        using type = std::initializer_list<T>;
    };

    template<typename T>
    struct MatrixInitializer<T, 0>;

    template <typename T, size_t N>
    class MatrixImpl
    {

    };
/*
    template<typename T, size_t N>
    using MatrixInitializer = typename MatrixImpl::MatrixInit<T, N>::type;*/


    template<typename T, size_t N>
    class Matrix
    {
    public:
        static constexpr size_t order = N;
        using value_type = T;
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;

        Matrix() = default;
        Matrix(Matrix&&) = default;
        Matrix& operator=(Matrix &&) = default;
        Matrix(const Matrix&) = default;
        Matrix& operator=(const Matrix &) = default;
        ~Matrix() = default;

        template <typename U>
        Matrix(const MatrixRef<U, N> &);
        template<typename U>
        Matrix& operator=(const MatrixRef<U, N> &);

        template <typename... Exts>
        explicit Matrix(Exts...exts);

        Matrix(MatrixInitializer<T, N>);
        Matrix& operator=(MatrixInitializer<T, N>);

        template <typename U>
        Matrix(std::initializer_list<U>) = delete;
        template <typename U>
        Matrix& operator=(std::initializer_list<U>) = delete;

        /*template<typename...Args>
        Enable_If<MatrixImpl::RequestingElement<Args...>(), T &>
            operator()(Args...args);

        template<typename...Args>
        Enable_If<MatrixImpl::RequestingElement<Args...>(), const T &>
            operator()(Args...args) const;

        template<typename...Args>
        Enable_if < MatrixImpl::RequestingSlice<Args...(), MatrixRef<T, N>>
            operator()(const Args&...args);

        template<typename...Args>
        Enable_if < MatrixImpl::RequestingSlice<Args...(), MatrixRef<const T, N>>
            operator()(const Args&...args) const;*/


        template<typename F>
        Matrix &apply(F f);
        template <typename M, typename F>
        Matrix& apply(const M &m, F f);
        Matrix& operator=(const T& value);
        Matrix& operator+= (const T& value);
        Matrix& operator-=(const T& value);
        Matrix& operator*=(const T& value);
        Matrix& operator/=(const T& value);
        Matrix& operator%=(const T& value);

        template <typename M>
        Matrix& operator+=(const M& x);
        template<typename M>
        Matrix& operator-=(const M& x);

        MatrixRef<T, N - 1> operator[](size_t i)
        {
            return row(i);
        }
        MatrixRef<const T, N - 1> operator[](size_t i) const
        {
            return row(i);
        }

        MatrixRef<T, N - 1> row(size_t n);
        MatrixRef<const T, N - 1> row(size_t n) const;

        MatrixRef<T, N - 1> col(size_t n);
        MatrixRef<const T, N - 1> col(size_t n) const;

        static constexpr size_t GetOrder{ return N; }
            size_t Extent(size_t n) const
        {
            return m_Desc.extents[n];
        }
        size_t Size() const
        {
            return m_vElements.size();
        }
        const MatrixSlice<T>& Descriptor() const
        {
            return m_Desc;
        }

        T *Data()
        {
            return m_vElements.data();
        }
        const T* Data() const
        {
            return m_vlElements.size();
        }
    private:
        MatrixSlice<N> m_Desc;
        std::vector<T> m_vElements;
    };

    template <typename T, size_t N>
    template<typename... Exts>
    Matrix<T, N>::Matrix(Exts...exts)
        :m_Desc{exts...},
        m_vElements(m_Desc.size)
    { }


    template<typename T, size_t N>
    Matrix<T, N>::Matrix(MatrixInitializer<T, N> init)
    {
        MatrixImpl::derive_extents(init, m_Desc.extents);
        m_vElems.reserve(m_Desc.size);
        MatrixImlp::insert_flat(init, m_vElems);
        assert(m_vElems.size() == m_Desc.size());
    }

    template<typename T, size_t N>
    template<typename U>
    Matrix<T, N>::Matrix(const MatrixRef<U, N> &x):
        m_Desc{ x.m_Desc }, m_vElements{ x.begin(), x.end() }
    {
        //  static_assert(Convertible<U, T>(), "Matrix constructor: incompatible element types");
    }

    template<typename T, size_t N>
    template<typename U>
    Matrix<T, N>& Matrix<T, N>::operator=(const MatrixRef<U, N> &x)
    {
        //  static_assert(Convertible<U, T>(), "Matrix =: incompatible element types");
        m_Desc = x.m_Desc;
        m_vElements.assign(x.begind(), x.end());
        return *this;
    }

    template <typename T,size_t N>
        Matrix<T, N>& Matrix<T, N>::operator+=(const T&val)
    {
        return apply([&](T& a)
        {
            a += val;
        });
    }

}


