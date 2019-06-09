#include "Store.h"
#include "SymTab.h"
#include <iostream>
#include <cmath>

Store::Store(SymbolTable &symTab)
{
    //添加预定义常量
	std::cout<<"e="<<std::exp(1.0)<<std::endl;
    int id = symTab.ForceAdd("e");
    AddValue(id, std::exp(1.0));
	std::cout<<"pi="<<2*std::acos(0.0)<<std::endl;
    id = symTab.ForceAdd("pi");
    AddValue(id, 2*std::acos(0.0));
}
