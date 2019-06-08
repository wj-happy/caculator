#pragma once

/*
 * 和数学函数相关
 */

#include "StrBuf.h"
#include "HTable.h"

const int idNotFound = -1;

class SymbolTable		//符号表
{ 
public: 
	explicit SymbolTable (int size);
	~SymbolTable();

    int ForceAdd (char const * str);
	int Find (char const * str) const;
	char const * GetString (int id) const;
private:
	HTable			_htab;	 // string -> ids
	int				_maxId;
    //字符串在缓冲器中的偏移
	int			  * _offStr; // id -> offset
	int				_curId;
	StringBuffer	_strBuf; // offset -> string
};
