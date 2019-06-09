#include "SymTab.h"
#include <iostream>
#include <cassert>

SymbolTable::SymbolTable()
    : _htab(hTabSize), _offStr(0)
{
}

size_t SymbolTable::ForceAdd(char const * str)
{
    int offset = _strBuf.Add(str);
    std::size_t id = _offStr.size();
    _offStr.push_back(offset);
    _htab.Add(str, id);
    return id;
}

// 不暴露哈希表内部细节
int SymbolTable::Find (char const * str) const
{
    for ( HTable::Seq seq(_htab, str);
          !seq.AtEnd(); seq.Advance() )
    {
        int id = seq.GetValue();
        int offStr = _offStr[id];
        if (_strBuf.IsEqual (offStr, str))
            return id;
    }

	return idNotFound;
}

char const * SymbolTable::GetString (int id) const
{
    assert ((id >= 0) && (id < _offStr.size()));
    int offStr = _offStr[id];
	return _strBuf.GetString (offStr);
}
