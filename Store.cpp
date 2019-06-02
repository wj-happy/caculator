#include "Store.h"
#include "SymTab.h"
#include <iostream>
#include <cmath>

Store::Store(int size, SymbolTable &symTab)
	: _size(size)
{
	_cell = new double[size];
	_status = new unsigned char[size];
	for (int i=0; i<size; ++i)
	{
		_status[i] = stNotInit;
	}

    //添加预定义常量
	std::cout<<"e="<<std::exp(1.0)<<std::endl;
	int id = symTab.ForceAdd("e", 1);
	SetValue(id, std::exp(1.0));
	std::cout<<"pi="<<2*std::acos(0.0)<<std::endl;
	id = symTab.ForceAdd("pi", 2);
	SetValue(id, 2*std::acos(0.0));
}
