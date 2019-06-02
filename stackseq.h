#ifndef STACKSEQ_H
#define STACKSEQ_H

/*
 * IStack类的迭代器
 * 友元函数：
 * 优点：能够提高效率，表达简单、清晰
 * 缺点：友元函数破环了封装机制，尽量不使用成员函数，除非不得已的情况下才使用友元函数
 */
#include "stack.h"

class StackSeq
{
public:
    StackSeq(const IStack & stack);
    bool AtEnd() const;
    void Advance();
    int GetNum() const;
private:
    //常量引用，不能调用其非常量函数
    //作为友元类，可以访问私有成员
    const IStack & _stack;
    int   _iCur;
};

#endif // STACKSEQ_H
