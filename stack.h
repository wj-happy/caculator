#ifndef ISTACK_H
#define ISTACK_H

const int initStack = 1;

template<class T>
class IStack
{
    //friend class StackSeq;
public:
    IStack();
    ~IStack();
    void Push(T value);
    T Pop();
    T Top() const;
    bool IsFull () const { return false; }
    bool IsEmpty () const;

public:
    class Seq
    {
    public:
        Seq(const IStack & stack);
        bool AtEnd() const;
        void Advance();
        int GetNum() const;
    private:
        //常量引用，不能调用其非常量函数
        //作为友元类，可以访问私有成员
        const IStack & _stack;
        int   _iCur;
    };

    friend class Seq;

private:
    void Grow ();
    T * _arr;
    int   _capacity; // size of the array
    int   _top;
};

/////////////实现

template<class T>
IStack<T>::IStack()
    : _capacity(initStack)
    , _top(0)
{
    _arr = new int[initStack];
}

template<class T>
IStack<T>::~IStack ()
{
    delete []_arr;
}

template<class T>
void IStack<T>::Push(T value)
{
    assert (_top <= _capacity);
    if (_top == _capacity)
    {
        Grow ();
    }
    _arr [_top] = value;
    ++_top;
}

template<class T>
T IStack<T>::Pop()
{
    assert(_top > 0);
    --_top;
    return _arr[_top];
}

template<class T>
T IStack<T>::Top() const
{
    assert(_top > 0);
    return _arr[_top-1];
}

template<class T>
bool IStack<T>::IsEmpty() const
{
    assert (_top >= 0);
    return _top == 0;
}

template<class T>
void IStack<T>::Grow()
{
    std::cout << "Doubling stack from " << _capacity << ".\n";
    T *arrNew = new T[2 * _capacity];
    memcpy(arrNew, _arr, _capacity * sizeof(T));
    _capacity = 2 * _capacity;
    delete []_arr;
    _arr = arrNew;
}


#endif // ISTACK_H
