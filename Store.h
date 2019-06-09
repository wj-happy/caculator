#pragma once

/*
 * 用于存储一些常量
 */

#include <cassert>
#include <vector>

class SymbolTable;	//前向声明

enum { stNotInit, stInit };

class Store
{
public:
    static const std::size_t idNotFound = 0xffffffff;
    Store(SymbolTable &symTab);
    bool IsInit(std::size_t id) const
	{
        assert(id != idNotFound);
        return ((id < _isInit.size()) && _isInit[id]);
	}
	double Value (int id) const
	{
		assert (IsInit (id));
		return _cell [id];
	}

    void AddValue (std::size_t id, double val)
	{
        assert(id >= 0);
        _cell.resize(id+1);
        _isInit.resize(id+1);
        _cell[id] = val;
        _isInit[id] = true;
	}
private:
    std::vector<double> _cell;
    std::vector<bool> _isInit;
};
