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
    SymbolTable symTab;
    FunctionTable funTab(symTab);
    Store store(maxSymbols, symTab);

    do
    {
        cout << "> ";
        cin.getline(buf, maxBuf);
        Scanner scanner(buf);
        if ( !scanner.IsEmpty() )
        {
            Parser parser(scanner, store, funTab, symTab);
            status = parser.Parse();
            //计算和打印分离
            if ( stOk == status )
            {
                double result = parser.Calculate();
                std::cout << "result is " << result << std::endl;
            }
            else
            {
                std::cout << "Syntax error.\n";
            }
        }
        else
        {
            break;
        }
    } while(status != stQuit);

    return 0;
}
