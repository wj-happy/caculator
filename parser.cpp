#include "Parser.h"
#include "Scanner.h"
#include "SymTab.h"
#include "Tree.h"
#include <iostream>

Parser::Parser (Scanner & scanner,
                Store & store,
                FunctionTable & funTab,
                SymbolTable & symTab)
  : _scanner (scanner),
    _pTree (0),
    _status (stOk),
    _funTab (funTab),
    _store (store),
    _symTab (symTab)
{}

Parser::~Parser ()
{
    delete _pTree;
}

Status Parser::Eval ()
{
    Parse();
    if (_status == stOk)
    {
        Execute();
    }
    else
    {
        _status = stQuit;
    }
    return _status;
}

void Parser::Execute()
{
    if (_pTree)
    {
        double result = _pTree->Calc();
        std::cout<<"  "<<result<<std::endl;
    }
}

void Parser::Parse()
{
    _pTree = Expr();
}

Node * Parser::Expr()
{
    Node *pNode = Term();
    cout << "--term: " << pNode->Calc() << endl;
    EToken token = _scanner.Token();

    if (token == tPlus)
    {
        _scanner.Accept();
        Node *pRight = Expr();
        pNode = new AddNode(pNode, pRight);
    }
    else if (token == tMinus)
    {
        _scanner.Accept ();
        Node * pRight = Expr ();
        pNode = new SubNode (pNode, pRight);
    }
    else if (token == tAssign)
    {
        _scanner.Accept ();
        Node * pRight = Expr ();
        if (pNode->IsLvalue ())
        {
            pNode = new AssignNode (pNode, pRight);
        }
        else
        {
            _status = stError;
            delete pNode;
            pNode = Expr ();
        }
    }

    return pNode;
}

Node * Parser::Term()
{
    Node *pNode = Factor();
    cout << "--Factor: " << pNode->Calc() << endl;

    if (_scanner.Token() == tMult)
    {
        _scanner.Accept();
        Node *pRight = Term();
        pNode = new MultNode(pNode, pRight);
    }
    else if (_scanner.Token() == tDivide)
    {
        _scanner.Accept();
        Node *pRight = Term();
        pNode = new DivideNode(pNode, pRight);
    }

    return pNode;
}

Node * Parser::Factor()
{
    Node *pNode;
    EToken token = _scanner.Token();

    if (token == tLParen)
    {
        _scanner.Accept();
        pNode = Expr();
        if (_scanner.Token() != tRParen)
        {
            _status = stError;
        }
        else
        {
            _scanner.Accept();
        }
    }
    else if (token == tNumber)
    {
        pNode = new NumNode(_scanner.Number());
        _scanner.Accept();
    }
    else if (token == tIdent)
    {
        char strSymbol[maxSymLen];
        int lenSym = maxSymLen;
        _scanner.GetSymbolName(strSymbol, lenSym);
        int id = _symTab.Find(strSymbol);
        _scanner.Accept();
        if (_scanner.Token() == tLParen)
        {
            _scanner.Accept();
            pNode = Expr();
            if (_scanner.Token() == tRParen)
            {
                _scanner.Accept();
            }
            else
            {
                _status = stError;
            }

            if (id != idNotFound && id < _funTab.Size ())
            {
                pNode = new FunNode (_funTab.GetFun (id), pNode);
            }
            else
            {
                std::cout << "Unknown function \"";
                std::cout << strSymbol << "\"\n";
            }
        }
        else
        {
            if (id == idNotFound)
            {
                id = _symTab.ForceAdd(strSymbol, lenSym);
            }
            pNode = new VarNode(id, _store);
        }
    }
    else if (token == tMinus)   //一元减
    {
        _scanner.Accept();
        pNode = new UMinusNode(Factor());
    }
    else if ( token == tPlus )  //一元加
    {
        _scanner.Accept();
        pNode = new UPlusNode(Factor());
    }
    else
    {
        _scanner.Accept();
        _status = stError;
        pNode = 0;
    }

    return pNode;
}
