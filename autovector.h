/*
 * 自定义容器类
 * 解决容器和智能指针所有权的问题
 */

#ifndef AUTOVECTOR_H
#define AUTOVECTOR_H

#include <cstddef>
#include <memory>
#include <cassert>

template<class T>
class auto_vector
{
public:
    typedef std::size_t size_t;
public:
    explicit auto_vector(size_t capacity=0);

    ~auto_vector();

    size_t size() const
    {
        return _end;
    }

    T const * operator [](size_t i) const;

//    T * operator [](size_t i)
//    {
//        //return _arr[i].get();
//    }

    void assign(size_t i, std::auto_ptr<T> & p);

    void assign_direct(size_t i, T * p);

    std::auto_ptr<T> pop_back();

    void push_back(std::auto_ptr<T> & p);

private:
    void grow(size_t reqCapacity);

    std::auto_ptr<T> * _arr;
    size_t _capacity;
    size_t _end;
};


#endif // AUTOVECTOR_H

template<class T>
auto_vector<T>::auto_vector(size_t capacity)
    : _arr(0), _capacity(capacity), _end(0)
{
}

template<class T>
auto_vector<T>::~auto_vector()
{
    delete []_arr;
}

template<class T>
const T *auto_vector<T>::operator [](size_t i) const
{
    return _arr[i].get();
}

template<class T>
void auto_vector<T>::assign(size_t i, std::auto_ptr<T> &p)
{
    assert(i < _end);
    _arr[i] = p;        //释放旧对象，转移新对象，p无效
}

template<class T>
void auto_vector<T>::assign_direct(size_t i, T *p)
{
    assert(i < _end);
    _arr[i].reset(p);
}

template<class T>
std::auto_ptr<T> auto_vector<T>::pop_back()
{
    assert(_end != 0);
    return _arr[--_end];
}

template<class T>
void auto_vector<T>::push_back(std::auto_ptr<T> &p)
{
    assert(_end <= _capacity);
    if ( _end == _capacity )
    {
        grow(_end + 1);
    }
    _arr[_end] = p;
    _end++;
}

template<class T>
void auto_vector<T>::grow(size_t reqCapacity)
{
    size_t newSize = 2 * _capacity;
    if ( reqCapacity > newSize )
    {
        newSize = reqCapacity;
    }

    //分配新数组
    std::auto_ptr<T> *arrNew = new std::auto_ptr<T>[newSize];
    //转移所有项
    for ( size_t i=0; i<_end; ++i )
    {
        arrNew[i] = _arr[i];
    }
    _capacity = newSize;

    if ( _arr != 0 )
    {
        delete []_arr;
    }
    _arr = arrNew;
}
