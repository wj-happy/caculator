#pragma once

#include "List.h"

class HTable	//实现字符串到整数的映射
{
    friend class IdSeq;
public:
    //显示构造函数
	explicit HTable(int size) : _size(size)
	{
		_aList = new List[size];
	}
	~HTable()
	{
		delete []_aList;
	}
	List const & Find(char const * str) const;
	void Add(char const * str, int id);
private:
	int hash(char const *str) const;
	List *_aList;
	int   _size;
};
