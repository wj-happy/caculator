#include "FunTab.h"
#include "SymTab.h"
#include <iostream>
#include <cassert>
#include <cmath>

double CoTan(double x);
double Cube (double x);

// 字符串和函数的映射表,static表示对外隐藏
FunctionEntry FunctionTable::_functionArray[] =
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
    std::sqrt,  "sqr",
    Cube, "cube"
};

FunctionTable::FunctionTable(SymbolTable &symTab)
    : _size(sizeof(_functionArray) / sizeof(_functionArray[0]))
{
    _pFun = new PtrFun[_size];
    std::cout << "*******FunctionTable********" << std::endl;
    for (int i=0; i<_size; ++i)
	{
        int len = strlen(_functionArray[i].strFun);
        _pFun[i] = _functionArray[i].pFun;
        std::cout << _functionArray[i].strFun << std::endl;
        int j = symTab.ForceAdd(_functionArray[i].strFun, len);
		assert(i == j);
	}
    std::cout << "**************************" << std::endl;
}

FunctionTable::~FunctionTable()
{
    delete []_pFun;
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

double Cube (double x)
{
    double y = std::pow(x, 1.0/3);
    return y;
}
