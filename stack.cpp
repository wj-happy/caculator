//#include "stack.h"
//#include <cassert>
//#include <iostream>

//IStack::IStack()
//    : _capacity(initStack)
//    , _top(0)
//{
//    _arr = new int[initStack];
//}

//IStack::~IStack ()
//{
//    delete []_arr;
//}

//void IStack::Push(T value)
//{
//    assert (_top <= _capacity);
//    if (_top == _capacity)
//    {
//        Grow ();
//    }
//    _arr [_top] = value;
//    ++_top;
//}

//int IStack::Pop()
//{
//    assert(_top > 0);
//    --_top;
//    return _arr[_top];
//}

//int IStack::Top() const
//{
//    assert(_top > 0);
//    return _arr[_top-1];
//}

//bool IStack::IsEmpty() const
//{
//    assert (_top >= 0);
//    return _top == 0;
//}

//void IStack::Grow()
//{
//    std::cout << "Doubling stack from " << _capacity << ".\n";
//    int *arrNew = new int[2 * _capacity];
//    memcpy(arrNew, _arr, _capacity * sizeof(int));
//    _capacity = 2 * _capacity;
//    delete []_arr;
//    _arr = arrNew;
//}
