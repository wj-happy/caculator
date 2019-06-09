#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "input.h"
#include "stack.h"

class Calculator
{
public:
    bool Execute(const Input & input);

    IStack<int> const & GetStack();

private:
    int Calculate(int num1, int num2, int token) const;
    IStack<int> _stack;
};

#endif // CALCULATOR_H
