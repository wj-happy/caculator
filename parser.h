#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <memory>
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

    Status Parse();

    double Calculate() const;

private:
    std::auto_ptr<Node> Expr();
    std::auto_ptr<Node> Term();
    std::auto_ptr<Node> Factor();

    Scanner			& _scanner;
    std::auto_ptr<Node> _pTree;
    Status           _status;
    Store			& _store;
    FunctionTable	& _funTab;
    SymbolTable		& _symTab;
};

#endif // PARSER_H
