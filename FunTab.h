#pragma once

class SymbolTable;

// 函数指针
typedef double(*PtrFun)(double);  //typedef 返回类型(*新类型)(参数表)

class FunctionEntry 
{ 
public: 
	PtrFun pFun; 
	char* strFun; 
};

//////////////////////////////////////////////////////////////////////////

class FunctionTable
{
public:
    FunctionTable(SymbolTable &symTab);
    ~FunctionTable();
	int Size () const { return _size; }
	PtrFun GetFun(int id) const { return _pFun [id]; }
private:
    static FunctionEntry _functionArray[];
    PtrFun	*_pFun;
	int		_size;
};
