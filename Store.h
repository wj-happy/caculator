#pragma once

/*
 * 用于存储一些常量
 */

#include <cassert>

class SymbolTable;	//前向声明

enum { stNotInit, stInit };

class Store
{
public:
	Store(int size, SymbolTable &symTab);
	~Store(void)
	{
		delete []_cell;
		delete []_status;
	}
	bool IsInit(int id) const
	{
		return ((id < _size) && (_status[id] != stNotInit));
	}
	double Value (int id) const
	{
		assert (IsInit (id));
		return _cell [id];
	}
	void SetValue (int id, double val)
	{
		if (id < _size)
		{
			_cell [id] = val;
			_status [id] = stInit;
		}
	}
private:
	int				_size;
    //单元数组
	double			*_cell;
    //状态数组
	unsigned char	*_status;
};
