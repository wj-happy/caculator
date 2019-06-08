#include "Tree.h"
#include "Store.h"
#include <iostream>
#include <cmath>

void Indent( int indent )
{
    for ( int i=0; i<indent; ++i )
    {
        std::cout << ' ';
    }
}

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

void AddNode::Print(int indent) const
{
    _pLeft->Print(indent + 2);
    Indent(indent);
    std::cout << "+" << std::endl;
    _pRight->Print(indent + 2);
    std::cout << std::endl;
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
        std::cerr << "Error: Division by zero\n";
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


double UPlusNode::Calc() const
{
    std::cout << "Unary plus\n";
    return _pChild->Calc();
}

MultiNode::MultiNode(Node *pNode)
    : _isError(false)
{
    _aChild[0] = pNode;
    _aIsPositive[0] = true;
    _iCur = 1;
}

void MultiNode::AddChild(Node *pNode, bool isPositive)
{
    if ( _iCur == MAX_CHILDREN )
    {
        _isError = true;
        return;
    }
    _aChild[_iCur] = pNode;
    _aIsPositive[_iCur] = isPositive;
    ++_iCur;
}

double SumNode::Calc() const
{
    if ( _isError )
    {
        std::cerr << "Error: too many terms\n";
        return 0.0;
    }

    double sum = 0.0;
    for ( int i=0; i<_iCur; ++i )
    {
        double val = _aChild[i]->Calc();
        if ( _aIsPositive[i] )
        {
            sum += val;
        }
        else
        {
            sum -= val;
        }
    }

    return sum;
}

double ProductNode::Calc() const
{
    if ( _isError )
    {
        std::cerr << "Error: too many terms\n";
        return 0.0;
    }

    double sum = 1;
    for ( int i=0; i<_iCur; ++i )
    {
        double val = _aChild[i]->Calc();
        if ( _aIsPositive[i] )
        {
            sum *= val;
        }
        else
        {
            if ( val < 0.000001 && val > -0.000001 )
            {
                std::cerr << "Error: zero";
                return HUGE_VAL;
            }
            else
            {
                sum /= val;
            }
        }
    }

    return sum;
}
