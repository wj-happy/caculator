#include <iostream>
#include "parser.h"
using namespace std;

const int maxBuf = 100;

int main()
{
    char buf[maxBuf];
    Status status;
    SymbolTable symTab;

    do
    {
        cout << "> ";
        cin.getline(buf, maxBuf);
        Scanner scanner(buf);
        Parser parser(scanner, symTab);
        status = parser.Eval();
    } while(status != stQuit);

    return 0;
}
