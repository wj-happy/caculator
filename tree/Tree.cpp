// (c) Bartosz Milewski 2000
#include "Tree.h"
#include <iostream>

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

double AddNode::Calc () const
{
	std::cout << "Adding\n";
	return _pLeft->Calc () + _pRight->Calc ();
}

double MultNode::Calc () const
{
	std::cout << "Multiplying\n";
	return _pLeft->Calc () * _pRight->Calc ();
}
