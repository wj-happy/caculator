//
// 扫描器
// 从左到右扫描输入的字符串(存放在文本缓冲器中)
// 将它们转换成一系列记号，并识别算术运算符、数字及标识符
//
// 标识符约定：以字母或下划线开头，还可以使用数字，有一定的长度限制(平均长度小于10)
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

const int MAX_SYM_LEN = 10;

// 记号
enum EToken
{
	tEnd,    // 结尾
	tError,  // 错误
	tNumber, // 数字
	tAdd,    // +
	tSub,    // -
	tMult,   // *
	tDivide, // /
	tMod,    // %
	tLParen, // (
	tRParen, // )
	tAssign, // =
	tIdent   // x, pi等符号名(标识符)

};

class Scanner
{
public:
    Scanner(const char* pszInputExp);
    ~Scanner();

	EToken Token() const;

	void Accept();

	// 将记号为tNumber的转换为浮点数
	double Number();

	void GetSymbolName(char* pszSymName, int& nLen);

	const char* GetInputExp() const;

private:
	// 略过输入中的空格
	void EatWhite();

private:
	// 存放一行文本的文本缓冲器
	// 最大长度由MAX_EXP_LEN控制
	const char* const m_pszInputExp;
	
	// 当前的扫描位置 
	int m_nCurPos;

	// 当前记号
	EToken m_eToken;

	// 存放记号为tNumber对应的浮点数
	double m_dblNumber;

	// 符号名的起始位置
	int m_nSymStartPos;
	// 符号名的长度
	int m_nSymLen;
};

