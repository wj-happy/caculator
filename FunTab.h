#pragma once

class SymbolTable;

const int maxIdFun = 16;

// ����ָ��
typedef double(*PtrFun)(double);  //typedef ��������(*������)(������)

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
	FunctionTable(SymbolTable &symTab, FunctionEntry funArr[]);
	int Size () const { return _size; }
	PtrFun GetFun(int id) const { return _pFun [id]; }
private:
	PtrFun	_pFun[maxIdFun];
	int		_size;
};

extern FunctionEntry funArr[];
