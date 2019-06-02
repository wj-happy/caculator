#include "HTable.h"
#include <cassert>

List const & HTable::Find (char const * str) const
{
	int i = hash (str);	
	return _aList [i];	
}

void HTable::Add (char const * str, int id)
{
	int i = hash (str);		//哈希值，可能多对一
	_aList [i].Add (id);	//id用来解决多对一的问题
}

// 哈希函数，将字符串转换为索引
int HTable::hash (char const * str) const
{
	// no empty strings, please
	assert (str != 0 && str [0] != 0);
    //--自定义算法(可能会重复，多个字符串对应一个id)
	unsigned h = str [0];
	for (int i = 1; str [i] != 0; ++i)
		h = (h << 4) + str [i];
	return h % _size; // remainder
}
