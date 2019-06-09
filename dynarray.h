#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <cassert>

template<class T>
class DynArray
{
    enum { initDynArray = 8 };
public:
    explicit DynArray(T const valDefault);
    ~DynArray();
    void Set(int i, T const val);
    //运算符重载
    T operator [](int i) const;
    T & operator [](int i);
    bool InRange(int i) const { return i < _capacity; }
private:
    void Grow(int len);

    T * _arr;
    int _capacity;
    T const _valDefault;
};

template<class T>
DynArray<T>::DynArray(const T valDefault)
    : _capacity(initDynArray)
    , _valDefault(valDefault)
{
    _arr = new T[_capacity];
    for ( int i=0; i<_capacity; ++i )
    {
        _arr[i] = valDefault;
    }
}

template<class T>
DynArray<T>::~DynArray()
{
    delete [] _arr;
}

template<class T>
void DynArray<T>::Set(int i, const T val)
{
    if ( i >= _capacity )
    {
        Grow(i);
    }
    _arr[i] = val;
}

template<class T>
T DynArray<T>::operator [](int i) const
{
    assert(i < _capacity && i >= 0);
    return _arr[i];
}

template<class T>
T &DynArray<T>::operator [](int i)
{
    assert(i < _capacity && i >= 0);
    return _arr[i];
}

template<class T>
void DynArray<T>::Grow(int len)
{
    int newSize = 2 * _capacity;
    if ( len >= newSize )
    {
       newSize = len + 1;
    }

    T * newArr = new T[newSize];
    assert(newArr);
    for ( int i=0; i<_capacity; ++i )
    {
        newArr[i] = _arr[i];
    }
    for ( int i=_capacity; i<newSize; ++i )
    {
        newArr[i] = _valDefault;
    }
    _capacity = newSize;

    delete [] _arr;
    _arr = newArr;
}

#endif // DYNARRAY_H
