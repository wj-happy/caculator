#include <iostream>
#include "parser.h"
#include "FunTab.h"
#include "Store.h"
#include "SymTab.h"
#include "Scanner.h"
using namespace std;

const int maxBuf = 100;

int main()
{
    try
    {
        char buf[maxBuf];
        Status status;
        SymbolTable symTab;
        FunctionTable funTab(symTab);
        Store store(symTab);

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
    }
    catch (std::bad_alloc)
    {
        std::cerr << "Out of memory\n";
    }
    catch (...)
    {
        std::cerr << "Internal error\n";
    }

    return 0;
}
