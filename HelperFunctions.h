#include <vector>
using namespace std;

class HelperFunctions
{
public:
    HelperFunctions(){};
    vector<unsigned int> toBinary(unsigned int n);
    unsigned int toDecimal(vector<unsigned int> bin);
};