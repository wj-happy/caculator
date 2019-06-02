#include "parser.h"

Parser::Parser(Scanner &Scanner, SymbolTable &SymTab)
    : _scanner(Scanner)
    , _symTab(SymTab)
{
    std::cout << " Parser created\n";
}

Parser::~Parser()
{
    std::cout << " Destoying Parser\n";
}

Status Parser::Eval()
{
    return stQuit;
}
