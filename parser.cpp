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

void Parser::Execute()
{
    if (_pTree)
    {
        double result = _pTree->Calc();
        std::cout<<"  "<<result<<std::endl;
    }
}

Status Parser::Parse()
{
    //一切都是表达式
    _pTree = Expr();
    if ( !_scanner.IsDone() )
    {
        _status = stError;
    }

    return _status;
}

double Parser::Calculate() const
{
    assert(_status == stOk);
    assert(_pTree != 0);
    return _pTree->Calc();
}

Node * Parser::Expr()
{
    Node *pNode = Term();
    EToken token = _scanner.Token();

    if (token == tPlus || token == tMinus)
    {
        MultiNode *pMultiNode = new SumNode(pNode);
        do
        {
            _scanner.Accept();
            Node *pRight = Term();
            pMultiNode->AddChild(pRight, (token==tPlus));
            token = _scanner.Token();
        } while(token == tPlus || token == tMinus);

        pNode = pMultiNode;
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

    EToken token = _scanner.Token();

    if (token == tMult || token == tDivide)
    {
        MultiNode *pMultiNode = new ProductNode(pNode);
        do
        {
            _scanner.Accept();
            Node *pRight = Factor();
            pMultiNode->AddChild(pRight, (token==tMult));
            token = _scanner.Token();
        } while(token==tMult || token==tDivide);

        pNode = pMultiNode;
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
        char strSymbol[maxSymLen+1];
        _scanner.GetSymbolName(strSymbol, maxSymLen+1);
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
                id = _symTab.ForceAdd(strSymbol);
                if ( id == idNotFound )
                {
                    std::cerr << "Error: too many variables\n";
                    _status = stError;
                    pNode = 0;
                }
            }

            if ( id != idNotFound )
            {
                pNode = new VarNode(id, _store);
            }
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
