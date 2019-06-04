#ifndef PARSER_H
#define PARSER_H

#include <iostream>
using namespace std;

class Node;
class Scanner;
class Store;
class FunctionTable;
class SymbolTable;

enum Status
{
    stOk,
    stQuit,
    stError
};

class Parser
{
public:
    Parser (Scanner & scanner, Store & store,
            FunctionTable & funTab,
            SymbolTable & symTab);
    ~Parser();

    //解析输入并进行计算
    Status Eval();

private:
    void Parse();
    Node * Expr();
    Node * Term();
    Node * Factor();
    void   Execute ();

    Scanner			& _scanner;
    Node			* _pTree;
    Status           _status;
    Store			& _store;
    FunctionTable	& _funTab;
    SymbolTable		& _symTab;
};

#endif // PARSER_H
