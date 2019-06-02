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

Status Parser::Parse()
{
    for ( EToken token = _scanner.Token();
          token != tEnd;
          _scanner.Accept() )
    {
        token = _scanner.Token();
        switch (token)
        {
        case tMult:
            std::cout << "Times\n";
            break;
        case tPlus:
            std::cout << "Plus\n";
            break;
        case tNumber:
            std::cout << "Number: " << _scanner.Number() << std::endl;
            break;
        case tEnd:
            std::cout << "End\n";
            return stQuit;
        case tError:
            std::cout << "Error\n";
            return stQuit;
        default:
            std::cout << "Error: bad token\n";
            return stQuit;
        }
    }

    return stOk;
}
