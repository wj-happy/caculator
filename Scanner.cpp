#include "Scanner.h"

#include <cassert>
#include <iostream>
using namespace std;


Scanner::Scanner(const char* pszInputExp)
	: m_pszInputExp(pszInputExp),
	  m_nCurPos(0)
{
	cout << "Scanner with \"" << m_pszInputExp << "\"" << endl;
	
	// 识别第一个记号
	Accept();
}


Scanner::~Scanner()
{
}

EToken Scanner::Token() const
{
	return m_eToken;
}

void Scanner::Accept()
{
	EatWhite();

	switch (m_pszInputExp[m_nCurPos])
	{
	case '+':
		m_eToken = tAdd;
		++m_nCurPos;
		break;
	case '-':
		m_eToken = tSub;
		++m_nCurPos;
		break;
	case '*':
		m_eToken = tMult;
		++m_nCurPos;
		break;
	case '/':
		m_eToken = tDivide;
		++m_nCurPos;
		break;
	case '%':
		m_eToken = tMod;
		++m_nCurPos;
		break;
	case '(':
		m_eToken = tLParen;
		++m_nCurPos;
		break;
	case ')':
		m_eToken = tRParen;
		++m_nCurPos;
		break;
	case '=':
		m_eToken = tAssign;
		++m_nCurPos;
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
		m_eToken = tNumber;
		char* pEnd;
		m_dblNumber = strtod(&m_pszInputExp[m_nCurPos], &pEnd);
		m_nCurPos = pEnd - m_pszInputExp;
		break;
	case '\0':
		m_eToken = tEnd;
		break;
	default:
		// 以字母或下划线打头的为标识符
		if (isalpha(m_pszInputExp[m_nCurPos])
		|| m_pszInputExp[m_nCurPos] == '_')
		{
			m_eToken = tIdent;
			m_nSymStartPos = m_nCurPos;

			do 
			{
				m_nCurPos++;
			} while (isalnum(m_pszInputExp[m_nCurPos]) || (m_pszInputExp[m_nCurPos] == '_'));

			m_nSymLen = m_nCurPos - m_nSymStartPos;
			if (m_nSymLen >= MAX_SYM_LEN)
			{
				m_nSymLen = MAX_SYM_LEN - 1;
			}
		}
		else
		{
			m_eToken = tError;
		}
		break;
	}
}

double Scanner::Number()
{
	assert(m_eToken == tNumber);
	return m_dblNumber;
}

void Scanner::EatWhite()
{
	while (isspace(m_pszInputExp[m_nCurPos]))
	{
		m_nCurPos++;
	}
}

void Scanner::GetSymbolName(char* pszSymName, int& nLen)
{
	assert(nLen >= MAX_SYM_LEN);
	//assert(m_nSynbolLen <= MAX_SYM_LEN);

	strncpy(pszSymName, &m_pszInputExp[m_nSymStartPos], m_nSymLen);
	pszSymName[m_nSymLen] = '\0';
	nLen = m_nSymLen;
}

const char* Scanner::GetInputExp() const
{
	return m_pszInputExp;
}

