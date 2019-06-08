#pragma once

//////////////////////////////////////////////////////////////////////////

class List
{
    friend class ListSeq;
public:
	List() : _pHead(0) {}
	~List(void);
	void Add(int id);

    // 链表结构体类： 嵌套类，隐藏实现细节
    class Link
    {
    public:
        Link(Link *pNext, int id) : _pNext(pNext), _id(id) {}
        //内联函数，提高效率
        int Id() const { return _id; }
        Link * Next() const { return _pNext; }
    private:
        int  _id;
        Link *_pNext;
    };

private:
    Link const * GetHead() const { return _pHead; }
	Link *_pHead;  //头指针
};

//////////////////////////////////////////////////////////////////////////

class ListSeq
{
public:
    bool AtEnd() const { return _pLink==0; }
    void Advance() { _pLink = _pLink->Next(); }
    int GetId() const { return _pLink->Id(); }
protected:
    //对于protected的函数，子类的“内部”的其他函数可以调用之
    ListSeq(List const & list)
        : _pLink(list.GetHead()) {}

private:
    //使用嵌套类需要加外部类
    List::Link const * _pLink;
};
