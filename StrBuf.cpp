#include "StrBuf.h"


int StringBuffer::Add(const char *str)
{
    assert(str);
    int len = strlen(str);
    int offset = _curOffset;
    if ( _curOffset + len >= _bufSize )
    {
        Reallocate(len + 1);
    }

    std::strcpy(&_buf [_curOffset], str);
    _curOffset += len + 1;
    return offset;
}

void StringBuffer::Reallocate(int addLen)
{
    int newSize = _bufSize * 2;
    if ( newSize < _curOffset + addLen )
    {
        newSize = _curOffset + addLen;
    }

    char *newBuf = new char[newSize];
    for ( int i=0; i<_curOffset; ++i )
    {
        newBuf[i] = _buf[i];
    }
    delete [] _buf;
    _buf = newBuf;
    _bufSize = newSize;
}
