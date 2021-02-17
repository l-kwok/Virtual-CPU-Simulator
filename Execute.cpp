#include <iostream>
#include "Execute.h"
using namespace std;
unsigned int Execute::executeOperation(unsigned int op, unsigned int src1, unsigned int src2)
{
    switch (op)
    {
    case 0:
        // cout << "add" << endl;
        return add(src1, src2);
        break;
    case 1:
        // cout << "sub" << endl;
        return sub(src1, src2);
        break;
    case 2:
        // cout << "mult" << endl;
        return mult(src1, src2);
        break;
    case 3:
        // cout << "div" << endl;
        return div(src1, src2);
        break;
    case 4:
        // cout << "mod" << endl;

        return mod(src1, src2);
        break;
    case 5:
        // cout << "beq" << endl;

        return beq(src1, src2);
        break;
    case 6:
        // cout << "bne" << endl;
        return bne(src1, src2);
        break;
    case 7:
        // cout << "mov" << endl;

        return src1;
        break;
    case 8:
        // cout << "Print" << endl;
        return src1;
        break;
    }
    return src1;
}