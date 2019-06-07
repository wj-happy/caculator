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

    Status Parse();

    double Calculate() const;

private:
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
