#pragma once

#include "List.h"

class HTable	//实现字符串到整数的映射
{
public:
    class Seq : public List<int>::Seq
    {
    public:
        Seq(HTable const &htab, char const *str)
            : List<int>::Seq(htab.Find(str)) {}
    };
    friend class Seq;

    //显示构造函数
	explicit HTable(int size) : _size(size)
	{
        _aList = new List<int>[size];
	}
	~HTable()
	{
		delete []_aList;
	}

	void Add(char const * str, int id);
private:
    List<int> const & Find(char const * str) const;
	int hash(char const *str) const;
    List<int> *_aList;
	int   _size;
};
