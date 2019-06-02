#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include "input.h"
using namespace std;

Input::Input()
{
    cin >> _buf;
    int c = _buf[0];
    if ( isdigit(c) )
    {
        _token = tokNumber;
    }
    else if ( c == '+' || c == '*' || c == '/' )
    {
        _token = c;
    }
    else if ( c == '-' )
    {
        if ( isdigit(c) )
        {
            _token = tokNumber;
        }
        else
        {
            _token = c;
        }
    }
    else
    {
        _token = tokError;
    }
}

int Input::Number() const
{
    assert( _token == tokNumber);
    return atoi(_buf);
}

