#include <utility>
#include <map>

using namespace std;

class RegisterFile
{
    //R0 to R15
    //Pair<Data, Valid> Name
    map<unsigned int, pair<unsigned int, bool>> registers;

public:
    RegisterFile();
    unsigned int getRegisterData(unsigned int reg);
    bool getRegisterValidity(unsigned int reg);
    bool setRegister(unsigned int reg, unsigned int data, unsigned int ins_type); //True: Register set, False: Register wasn't set
    void printStack();
};