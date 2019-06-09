#pragma once

//////////////////////////////////////////////////////////////////////////

template<class T>
class List
{
public:
    List();
    ~List();
    void Add(T value);

private:
    // 链表结构体类： 嵌套类，隐藏实现细节
    class Link
    {
    public:
        Link(Link *pNext, int value) : _pNext(pNext), _value(value) {}
        //内联函数，提高效率
        T Value() const { return _value; }
        Link * Next() const { return _pNext; }
    private:
        T  _value;
        Link *_pNext;
    };

public:
    class Seq
    {
    public:
        bool AtEnd() const { return _pLink==0; }
        void Advance() { _pLink = _pLink->Next(); }
        int GetValue() const { return _pLink->Value(); }
    protected:
        //对于protected的函数，子类的“内部”的其他函数可以调用之
        Seq(List const & list)
            : _pLink(list.GetHead()) {}

    private:
        //使用嵌套类需要加外部类
        Link const * _pLink;
    };

    friend class Seq;

private:
    Link const * GetHead() const { return _pHead; }
	Link *_pHead;  //头指针
};

template<class T>
List<T>::List()
    : _pHead(0)
{
}

template<class T>
List<T>::~List()
{
    while (_pHead != 0)  //释放链表
    {
        Link *pLink = _pHead;
        _pHead = _pHead->Next();
        delete pLink;
    }
}

template<class T>
void List<T>::Add(T value)  //头插法
{
    Link *pLink = new Link(_pHead, value);
    _pHead = pLink;
}

