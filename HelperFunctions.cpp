#include "HelperFunctions.h"

using namespace std;

vector<unsigned int> HelperFunctions::toBinary(unsigned int n)
{
    vector<unsigned int> result(32, 0);
    for (int i = result.size() - 1; i >= 0; --i)
    {
        if (n % 2)
        {
            result[i] = 1;
        }
        n = n / 2;
    }
    return result;
}

unsigned int HelperFunctions::toDecimal(vector<unsigned int> bin)
{
    unsigned int result = 0;
    unsigned int base = 1;
    for (int i = bin.size() - 1; i >= 0; --i)
    {
        result += bin[i] * base;
        base = base * 2;
    }
    return result;
}