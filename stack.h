#ifndef ISTACK_H
#define ISTACK_H

const int initStack = 1;

class IStack
{
    friend class StackSeq;
public:
    IStack();
    ~IStack();
    void Push(int i);
    int Pop();
    int Top() const;
    bool IsFull () const { return false; }
    bool IsEmpty () const;

private:
    void Grow ();
    int * _arr;
    int   _capacity; // size of the array
    int   _top;
};

#endif // ISTACK_H
