#include "Tree.h"
#include "Store.h"
#include <iostream>
#include <cmath>

double NumNode::Calc () const
{
	std::cout << "Numeric node " << _num << std::endl;
	return _num;
}

BinNode::~BinNode ()
{
	delete _pLeft;
	delete _pRight;
}

UniNode::~UniNode ()
{
    delete _pChild;
}

double AddNode::Calc () const
{
	std::cout << "Adding\n";
	return _pLeft->Calc () + _pRight->Calc ();
}

double SubNode::Calc () const
{
    std::cout << "Subtracting\n";
    return _pLeft->Calc () - _pRight->Calc ();
}

double MultNode::Calc () const
{
	std::cout << "Multiplying\n";
	return _pLeft->Calc () * _pRight->Calc ();
}

double DivideNode::Calc () const
{
    std::cout << "Dividing\n";
    double divisor = _pRight->Calc ();
    if (divisor > 0.000001 || divisor < -0.000001 )
    {
        return _pLeft->Calc () / divisor;
    }
    else
    {
        std::cout << "Error: Division by zero\n";
        return HUGE_VAL;
    }
}

double FunNode::Calc() const
{
    std::cout<<"Function call\n";
    assert(_pFun != 0);
    return (*_pFun)(_pChild->Calc());
}

double UMinusNode::Calc () const
{
    std::cout << "Unary minus\n";
    return - _pChild->Calc();
}

double AssignNode::Calc () const
{
    std::cout << "Assigning\n";
    double x = _pRight->Calc ();
    _pLeft->Assign (x);
    return x;
}

double VarNode::Calc() const
{
    std::cout<<"Variable\n";
    double x = 0.0;
    if (_store.IsInit(_id))
    {
        x = _store.Value(_id);
    }
    else
    {
        std::cout<<"Use of uninitialized variable\n";
    }
    return x;
}

void VarNode::Assign (double val)
{
    _store.SetValue (_id, val);
}

bool VarNode::IsLvalue () const
{
    return true;
}
