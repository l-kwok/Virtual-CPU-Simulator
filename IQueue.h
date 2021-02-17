#include <vector>
#include "Instruction.h"

using namespace std;

class IQ
{
    struct qNode{
        Instruction* ins;
        unsigned int ROB_ID;
    };
    const unsigned int MAX_SIZE = 20; //maximum 20 instructions
    HelperFunctions hf;
    vector<qNode> iqueue;
public:
    IQ();
    ~IQ();
    void printIQ();
    bool push(Instruction* ins, unsigned int id);
    void pop();
    bool isEmpty();
    Instruction* front();
    Instruction* find(unsigned int index);
    unsigned int getSize();
    void clear() {iqueue.clear();};

};