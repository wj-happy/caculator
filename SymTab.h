#pragma once

/*
 * 和数学函数相关
 */

#include "StrBuf.h"
#include "HTable.h"
#include "dynarray.h"

class SymbolTable		//符号表
{ 
    enum { hTabSize = 65 };
public: 
    enum { idNotFound = -1 };

    SymbolTable ();

    int ForceAdd (char const * str);
	int Find (char const * str) const;
	char const * GetString (int id) const;
private:
	HTable			_htab;	 // string -> ids
	int				_maxId;
    //字符串在缓冲器中的偏移
    DynArray<int>	 _offStr; // id -> offset
	int				_curId;
	StringBuffer	_strBuf; // offset -> string
};
