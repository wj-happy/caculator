#include <iostream>
#include "calculator.h"
#include "stackseq.h"
using namespace std;


int main()
{
    Calculator theCalculator;
    bool status;

    do
    {
        cout << "> ";
        Input input;
        status = theCalculator.Execute(input);
        if ( status )
        {
            for ( StackSeq seq(theCalculator.GetStack());
                  !seq.AtEnd();
                  seq.Advance() )
            {
                cout << " " << seq.GetNum() << endl;
            }
        }
    } while(status);

    return 0;
}
