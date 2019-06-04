#pragma once

//链表结构体类
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

//////////////////////////////////////////////////////////////////////////

class List
{
public:
	List() : _pHead(0) {}
	~List(void);
	void Add(int id);
	Link const * GetHead() const { return _pHead; }
private:
	Link *_pHead;  //头指针
};
