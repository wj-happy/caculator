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
    return _eToken;
}

void Scanner::Accept()
{
	EatWhite();

    switch (_buf[_iLook])
	{
	case '+':
        _eToken = tPlus;
        ++_iLook;
		break;
	case '-':
        _eToken = tMinus;
        ++_iLook;
		break;
	case '*':
        _eToken = tMult;
        ++_iLook;
		break;
	case '/':
        _eToken = tDivide;
        ++_iLook;
		break;
	case '%':
        _eToken = tMod;
        ++_iLook;
		break;
	case '(':
        _eToken = tLParen;
        ++_iLook;
		break;
	case ')':
        _eToken = tRParen;
        ++_iLook;
		break;
	case '=':
        _eToken = tAssign;
        ++_iLook;
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '.':
    {
        _eToken = tNumber;
		char* pEnd;
        //字符串转double
        _number = strtod(&_buf[_iLook], &pEnd);
        _iLook = pEnd - _buf;
    }
		break;
	case '\0':
        _eToken = tEnd;
		break;
	default:
		// 以字母或下划线打头的为标识符
        if (isalpha(_buf[_iLook])
        || _buf[_iLook] == '_')
		{
            _eToken = tIdent;
            _lenSymbol = _iLook;

			do 
			{
                _iLook++;
            } while (isalnum(_buf[_iLook]) || (_buf[_iLook] == '_'));

            _iSymbol = _iLook - _lenSymbol;
            if (_iSymbol >= MAX_SYM_LEN)
			{
                _iSymbol = MAX_SYM_LEN - 1;
			}
		}
		else
		{
            _eToken = tError;
		}
		break;
	}
}

double Scanner::Number()
{
    assert(_eToken == tNumber);
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

void Scanner::GetSymbolName(char* pszSymName, int& nLen)
{
    assert(nLen >= MAX_SYM_LEN);
	//assert(m_nSynbolLen <= MAX_SYM_LEN);

    strncpy(pszSymName, &_buf[_lenSymbol], _iSymbol);
    pszSymName[_iSymbol] = '\0';
    nLen = _iSymbol;
}

const char* Scanner::GetInputExp() const
{
    return _buf;
}

