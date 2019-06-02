#if !defined (TREE_H)
#define TREE_H
// (c) Bartosz Milewski 2000

/*
 * 通过算数树实现表达式
 */

// 抽象类
class Node
{
public:
	virtual ~Node () {}
	virtual double Calc () const = 0;
};

// 表示一个数
class NumNode: public Node
{
public:
	NumNode (double num) : _num (num ) {}
	double Calc () const;
private:
	const double _num;
};

// 表示一个二元运算符
class BinNode: public Node
{
public:
	BinNode (Node * pLeft, Node * pRight)
		: _pLeft (pLeft), _pRight (pRight) {}
	~BinNode ();
protected: 
	Node * const _pLeft;
	Node * const _pRight;
};

// +
class AddNode: public BinNode
{
public:
	AddNode (Node * pLeft, Node * pRight)
		: BinNode (pLeft, pRight) {}
	double Calc () const;
};

// *
class MultNode: public BinNode
{
public:
	MultNode (Node * pLeft, Node * pRight)
		: BinNode (pLeft, pRight) {}
	double Calc () const;
};

#endif
