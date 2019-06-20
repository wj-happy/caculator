#if !defined (TREE_H)
#define TREE_H
// (c) Bartosz Milewski 2000

/*
 * 通过算数树实现表达式
 */

#include "FunTab.h"
//#include "dynarray.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <memory>
#include "autovector.h"

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
    BinNode (std::auto_ptr<Node> & pLeft, std::auto_ptr<Node> & pRight)
		: _pLeft (pLeft), _pRight (pRight) {}
protected: 
    std::auto_ptr<Node> _pLeft;
    std::auto_ptr<Node> _pRight;
};

// 一般性多节点
class MultiNode : public Node
{
public:
    MultiNode(std::auto_ptr<Node> & pNode);
    void AddChild(std::auto_ptr<Node> & pNode, bool isPositive);
protected:

    //这种方式有问题
    //std::vector<std::auto_ptr<Node> > _aChild;

    auto_vector<Node> _aChild;
    std::vector<bool> _aIsPositive;
};

class SumNode : public MultiNode
{
public:
    SumNode(std::auto_ptr<Node> & pNode) : MultiNode(pNode) {}
    double Calc() const;
};

class ProductNode : public MultiNode
{
public:
    ProductNode(std::auto_ptr<Node> & pNode) : MultiNode(pNode) {}
    double Calc() const;
};

// +
class AddNode: public BinNode
{
public:
    AddNode (std::auto_ptr<Node> & pLeft, std::auto_ptr<Node> & pRight)
		: BinNode (pLeft, pRight) {}
	double Calc () const;
    void Print(int indent=0) const;
};

class SubNode: public BinNode
{
public:
    SubNode (std::auto_ptr<Node> & pLeft, std::auto_ptr<Node> & pRight)
        : BinNode (pLeft, pRight) {}
    double Calc () const;
};

// *
class MultNode: public BinNode
{
public:
    MultNode (std::auto_ptr<Node> & pLeft, std::auto_ptr<Node> & pRight)
		: BinNode (pLeft, pRight) {}
	double Calc () const;
};

class DivideNode: public BinNode
{
public:
    DivideNode (std::auto_ptr<Node> & pLeft, std::auto_ptr<Node> & pRight)
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
    UniNode (std::auto_ptr<Node> & pChild)
        : _pChild (pChild) {}       //转移构造函数
protected:
    std::auto_ptr<Node> _pChild;
};

class AssignNode : public BinNode
{
public:
    AssignNode (std::auto_ptr<Node> & pLeft, std::auto_ptr<Node> & pRight)
        : BinNode (pLeft, pRight)
    {
        assert (pLeft->IsLvalue ());
    }
    double Calc () const;
};

class FunNode: public UniNode
{
public:
    FunNode (PtrFun pFun, std::auto_ptr<Node> & pNode)
        : UniNode (pNode), _pFun (pFun)
    {}
    double Calc () const;
private:
    PtrFun       _pFun;
};

class UMinusNode: public UniNode
{
public:
    UMinusNode (std::auto_ptr<Node> & pNode)
        : UniNode (pNode) {}
    double Calc () const;
};

// 一元加运算符
class UPlusNode : public UniNode
{
public:
    UPlusNode (std::auto_ptr<Node> & pNode)
        : UniNode(pNode) {}
    double Calc () const;
};

#endif
