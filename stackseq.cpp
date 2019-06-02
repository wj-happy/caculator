#include "stackseq.h"
#include <cassert>

StackSeq::StackSeq(const IStack & stack)
    : _stack(stack)
    , _iCur(0)
{

}

bool StackSeq::AtEnd() const
{
    return _iCur == _stack._top;
}

void StackSeq::Advance()
{
    assert( !AtEnd() );
    ++_iCur;
}

int StackSeq::GetNum() const
{
    assert( !AtEnd() );
    return _stack._arr[_iCur];
}
