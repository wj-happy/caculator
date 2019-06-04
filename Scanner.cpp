#include "Scanner.h"

#include <cassert>
#include <iostream>
using namespace std;


Scanner::Scanner(const char* buf)
    : _buf(buf),
      _iLook(0)
{
    cout << "Scanner with \"" << _buf << "\"" << endl;
	
	// 识别第一个记号
	Accept();
}


Scanner::~Scanner()
{
}

EToken Scanner::Token() const
{
    return _token;
}

EToken Scanner::Accept()
{
    //去除空格
    EatWhite ();
    switch (_buf[_iLook])
    {
    case '+':
        _token = tPlus;
        ++_iLook;
        break;
    case '-':
        _token = tMinus;
        ++_iLook;
        break;
    case '*':
        _token = tMult;
        ++_iLook;
        break;
    case '/':
        _token = tDivide;
        ++_iLook;
        break;
    case '=':
        _token = tAssign;
        ++_iLook;
        break;
    case '(':
        _token = tLParen;
        ++_iLook;
        break;
    case ')':
        _token = tRParen;
        ++_iLook;
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case '.':
        {
            _token = tNumber;
            char *p;
            _number = std::strtod(&_buf[_iLook], &p);	//string->double, p: Pointer to character that stops scan
            _iLook = p - _buf;
        }
        break;
    case '\0': // end of input
        _token = tEnd;
        break;
    default:    // 变量
        if (isalpha(_buf[_iLook]) || (_buf[_iLook] == '_'))
        {
            _token = tIdent;
            //计算符号变量的长度
            _iSymbol = _iLook;
            int cLook;
            do
            {
                cLook = _buf[++_iLook];
            } while (isalnum(cLook) || cLook == '_');
            _lenSymbol = _iLook - _iSymbol;
            if (_lenSymbol >= maxSymLen)
            {
                _lenSymbol = maxSymLen - 1;
            }
        }
        else
        {
            _token = tError;
        }
        break;
    }

    return _token;
}
double Scanner::Number()
{
    assert(_token == tNumber);
    return _number;
}

void Scanner::EatWhite()
{
    while (isspace(_buf[_iLook]))
	{
        _iLook++;
	}
}

int Scanner::nSymStartPos() const
{
    return _lenSymbol;
}

void Scanner::GetSymbolName(char *strOut, int &len)
{
    assert(len >= maxSymLen);
    assert(_lenSymbol <= maxSymLen);
    std::strncpy(strOut, &_buf[_iSymbol], _lenSymbol);
    strOut[_lenSymbol] = '\0';
    len = _lenSymbol;
}

const char* Scanner::GetInputExp() const
{
    return _buf;
}

