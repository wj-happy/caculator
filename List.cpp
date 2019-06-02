#include "List.h"
#include <iostream>

List::~List(void)
{
	while (_pHead != 0)  //释放链表
	{
		Link *pLink = _pHead;
		_pHead = _pHead->Next();
		delete pLink;
	}
}

void List::Add(int id)  //头插法
{
	Link *pLink = new Link(_pHead, id);
	_pHead = pLink;
}
