#include <iostream>
#include <cassert>
#include "calculator.h"

bool Calculator::Execute(const Input &input)
{
    int token = input.Token ();
    bool status = false; // assume failure

    if (token == tokError)
    {
        std::cout << "Unknown token\n";
    }
    else if (token == tokNumber)
    {
        if (_stack.IsFull ())
        {
            std::cout << "Stack is full\n";
        }
        else
        {
            _stack.Push (input.Number ());
            status = true; // success
        }
    }
    else
    {
        assert (token == '+' || token == '-'
             || token == '*' || token == '/');
        if (_stack.IsEmpty ())
        {
            std::cout << "Stack is empty\n";
        }
        else
        {
            int num2 = _stack.Pop ();
            int num1;

            // Special case, when only one number on the stack:
            // use this number for both operands.

            if (_stack.IsEmpty ())
                num1 = num2;
            else
                    num1 = _stack.Pop ();

            _stack.Push (Calculate (num1, num2, token));
            status = true;
        }
    }
    return status;
}

const IStack<int> &Calculator::GetStack()
{
    return _stack;
}

int Calculator::Calculate(int num1, int num2, int token) const
{
    int result;

    if (token == '+')
        result = num1 + num2;
    else if (token == '-')
        result = num1 - num2;
    else if (token == '*')
        result = num1 * num2;
    else if (token == '/')
    {
        if (num2 == 0)
        {
            std::cout << "Division by zero\n";
            result = 0;
        }
        else
            result = num1 / num2;
    }
    return result;
}
