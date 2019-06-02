#ifndef PARSER_H
#define PARSER_H

#include <iostream>
using namespace std;
#include "Scanner.h"
#include "symboltable.h"


enum Status
{
    stOk,
    stQuit,
    stError
};

class Parser
{
public:
    Parser(Scanner& Scanner, SymbolTable& SymTab);
    ~Parser();

    Status Eval();

    Status Parse();

private:
    Scanner & _scanner;
    SymbolTable & _symTab;
};

#endif // PARSER_H
