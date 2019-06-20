#include "SymTab.h"
#include <iostream>
#include <cassert>
#include <iterator>

SymbolTable::SymbolTable()
    : _id(0)
{
}

size_t SymbolTable::ForceAdd(char const * str)
{
    std::string s(str);
    _dictionary[s] = _id;
    return _id++;
}

// 不暴露哈希表内部细节
size_t SymbolTable::Find(char const * str) const
{
    std::map<std::string, std::size_t>::const_iterator it;
    it = _dictionary.find(str);
    if ( it != _dictionary.end() )
    {
        return it->second;
    }

	return idNotFound;
}
