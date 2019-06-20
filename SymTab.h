#pragma once

/*
 * 和数学函数相关
 */

#include "dynarray.h"
#include <vector>
#include <map>
#include <string>

class SymbolTable		//符号表
{ 
public: 
    static const std::size_t idNotFound = 0xffffffff;

    SymbolTable ();

    std::size_t ForceAdd (char const * str);
    std::size_t Find (char const * str) const;
private:
    std::map<std::string, std::size_t> _dictionary;
    std::size_t _id;
};
