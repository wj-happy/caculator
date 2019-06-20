#include "Parser.h"
#include "Tree.h"
#include "Scanner.h"
#include "SymTab.h"
#include <iostream>

Parser::Parser (Scanner & scanner,
                Store & store,
                FunctionTable & funTab,
                SymbolTable & symTab)
  : _scanner (scanner),
    _status (stOk),
    _funTab (funTab),
    _store (store),
    _symTab (symTab)
{}

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
    assert(_pTree.get() != 0);
    return _pTree->Calc();
}

std::auto_ptr<Node> Parser::Expr()
{
    std::auto_ptr<Node> pNode = Term();
    if ( pNode.get() == 0 )
    {
        return pNode;
    }

    EToken token = _scanner.Token();

    if (token == tPlus || token == tMinus)
    {
        std::auto_ptr<MultiNode> pMultiNode(new SumNode(pNode));
        do
        {
            _scanner.Accept();
            std::auto_ptr<Node> pRight = Term();
            if ( pRight.get() == 0 )
            {
                return pNode;
            }

            //std::cout << "---before: " << pRight.get();
            pMultiNode->AddChild(pRight, (token==tPlus));
            //std::cout << "---after: " << pRight.get();
            token = _scanner.Token();
        } while(token == tPlus || token == tMinus);

        pNode = pMultiNode;
    }
    else if (token == tAssign)
    {
        _scanner.Accept ();
        std::auto_ptr<Node> pRight = Expr ();
        if ( pRight.get() == 0 )
        {
            return pNode;
        }
        if (pNode->IsLvalue ())
        {
            pNode = std::auto_ptr<Node>(new AssignNode (pNode, pRight));
        }
        else
        {
            _status = stError;
            pNode = Expr ();
        }
    }

    return pNode;
}

std::auto_ptr<Node> Parser::Term()
{
    std::auto_ptr<Node> pNode = Factor();

    EToken token = _scanner.Token();

    if (token == tMult || token == tDivide)
    {
        std::auto_ptr<MultiNode> pMultiNode(new ProductNode(pNode));
        do
        {
            _scanner.Accept();
            std::auto_ptr<Node> pRight = Factor();
            pMultiNode->AddChild(pRight, (token==tMult));
            token = _scanner.Token();
        } while(token==tMult || token==tDivide);

        pNode = pMultiNode;
    }

    return pNode;
}

std::auto_ptr<Node> Parser::Factor()
{
    auto_ptr<Node> pNode;
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
        pNode = auto_ptr<Node>(new NumNode(_scanner.Number()));
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

            if (id != SymbolTable::idNotFound && id < _funTab.Size ())
            {
                pNode = auto_ptr<Node>(new FunNode (_funTab.GetFun (id), pNode));
            }
            else
            {
                std::cout << "Unknown function \"";
                std::cout << strSymbol << "\"\n";
            }
        }
        else
        {
            if (id == SymbolTable::idNotFound)
            {
                id = _symTab.ForceAdd(strSymbol);
            }

            assert( id != SymbolTable::idNotFound );
            pNode = auto_ptr<Node>(new VarNode(id, _store));
        }
    }
    else if (token == tMinus)   //一元减
    {
        _scanner.Accept();
        auto_ptr<Node> ptr = Factor();
        pNode = auto_ptr<Node>(new UMinusNode(ptr));
    }
    else if ( token == tPlus )  //一元加
    {
        _scanner.Accept();
        auto_ptr<Node> ptr = Factor();
        pNode = auto_ptr<Node>(new UPlusNode( ptr ));
    }
    else
    {
        _scanner.Accept();
        _status = stError;
    }

    return pNode;
}
