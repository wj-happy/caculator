#include "FunTab.h"
#include "SymTab.h"
#include <iostream>
#include <cassert>
#include <cmath>

double CoTan(double x);

// 字符串和函数的映射表
FunctionEntry funArr[maxIdFun] =
{
    std::log,	"log",
    std::log10,	"log10",
    std::exp,	"exp",
    std::sqrt,	"sqrt",
    std::sin,	"sin",
    std::cos,	"cos",
    std::tan,	"tan",
    CoTan,	"cotan",
    std::sinh,	"sinh",		//双曲正弦函数
    std::cosh,	"cosh",
    std::tanh,	"tanh",
    std::asin,	"asin",
    std::acos,	"acos",
    std::atan,	"atan",
	0,		""			//??
};

FunctionTable::FunctionTable(SymbolTable &symTab, FunctionEntry funArr[])
	: _size(0)
{
	for (int i=0; i<maxIdFun; ++i)
	{
		int len = strlen(funArr[i].strFun);
		if (len == 0)
		{
			break;;
		}
		_pFun[i] = funArr[i].pFun;
		std::cout<<funArr[i].strFun<<std::endl;
		int j = symTab.ForceAdd(funArr[i].strFun, len);
		assert(i == j);
		++_size;
	}
}

double CoTan (double x) 
{
	double y = std::tan (x);
	if (y == 0)
	{
		std::cout << "cotan of " << x << " undefined\n";
		return HUGE_VAL;
	}
	return 1.0 / y;
}
