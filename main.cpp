#include <iostream>
#include "parser.h"
#include "FunTab.h"
#include "Store.h"
#include "SymTab.h"
#include "Scanner.h"
using namespace std;

const int maxBuf = 100;
const int maxSymbols = 40;

int main()
{
    char buf[maxBuf];
    Status status;
    SymbolTable symTab(maxSymbols);
    FunctionTable funTab(symTab, funArr);
    Store store(maxSymbols, symTab);

    do
    {
        cout << "> ";
        cin.getline(buf, maxBuf);
        Scanner scanner(buf);
        Parser parser(scanner, store, funTab, symTab);
        status = parser.Eval();
    } while(status != stQuit);

    return 0;
}
