#pragma once

#include "HTable.h"
#include <cstring>
#include <cassert>

const int maxBufSize = 500;

// 类似string类
class StringBuffer
{
public:
    StringBuffer() : _buf(0), _bufSize(0), _curOffset(0) {}

    ~StringBuffer(void)
    {
        delete []_buf;
    }
    bool WillFit (int len) const
    {
        return _curOffset + len + 1 <= _bufSize;
    }
    int Add(char const * str);

    int GetOffset () const
    {
        return _curOffset;
    }
    bool IsEqual (int offStr, char const * str) const
    {
        char const * strStored = &_buf [offStr];
        return std::strcmp (str, strStored) == 0;
    }
    char const * GetString (int offStr) const
    {
        assert(offStr < _curOffset);
        return &_buf [offStr];
    }
private:
    void Reallocate(int addLen);

    int	_bufSize;
    char	*_buf;
    int	_curOffset;
};
