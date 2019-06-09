#if !defined (TREE_H)
#define TREE_H
// (c) Bartosz Milewski 2000

/*
 * 通过算数树实现表达式
 */

#include "FunTab.h"
#include "dynarray.h"
#include <cassert>
#include <iostream>

class Store;

// 抽象类
class Node
{
public:
	virtual ~Node () {}
	virtual double Calc () const = 0;
    virtual bool IsLvalue () const
    { return false; }
    virtual void Assign (double)
    {
        assert (!"Assign called incorrectly");
    }
    virtual void Print(int indent=0) const
    {
        std::cout << indent << std::endl;
    }
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

// 一般性多节点
class MultiNode : public Node
{
public:
    MultiNode(Node *pNode);
    ~MultiNode() {}
    void AddChild(Node *pNode, bool isPositive);
protected:
    int _iCur;
    DynArray<Node*> _aChild;
    DynArray<bool> _aIsPositive;
};

class SumNode : public MultiNode
{
public:
    SumNode(Node *pNode) : MultiNode(pNode) {}
    double Calc() const;
};

class ProductNode : public MultiNode
{
public:
    ProductNode(Node *pNode) : MultiNode(pNode) {}
    double Calc() const;
};

// +
class AddNode: public BinNode
{
public:
	AddNode (Node * pLeft, Node * pRight)
		: BinNode (pLeft, pRight) {}
	double Calc () const;
    void Print(int indent=0) const;
};

class SubNode: public BinNode
{
public:
    SubNode (Node * pLeft, Node * pRight)
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

class DivideNode: public BinNode
{
public:
    DivideNode (Node * pLeft, Node * pRight)
        : BinNode (pLeft, pRight) {}
    double Calc () const;
};

// 表示一个常量
class VarNode : public Node
{
public:
    VarNode (int id, Store & store)
        : _id (id), _store (store) {}
    double Calc () const;
    bool IsLvalue () const;
    void Assign (double val);
private:
    const int _id;
    Store &_store;
};

class UniNode: public Node
{
public:
    UniNode (Node * pChild)
        : _pChild (pChild) {}
    ~UniNode ();
protected:
    Node * const _pChild;
};

class AssignNode : public BinNode
{
public:
    AssignNode (Node * pLeft, Node * pRight)
        : BinNode (pLeft, pRight)
    {
        assert (pLeft->IsLvalue ());
    }
    double Calc () const;
};

class FunNode: public UniNode
{
public:
    FunNode (PtrFun pFun, Node * pNode)
        : UniNode (pNode), _pFun (pFun)
    {}
    double Calc () const;
private:
    PtrFun       _pFun;
};

class UMinusNode: public UniNode
{
public:
    UMinusNode (Node * pNode)
        : UniNode (pNode) {}
    double Calc () const;
};

// 一元加运算符
class UPlusNode : public UniNode
{
public:
    UPlusNode (Node * pNode)
        : UniNode(pNode) {}
    double Calc () const;
};

#endif
