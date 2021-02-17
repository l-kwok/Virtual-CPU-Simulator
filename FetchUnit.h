#include "Memory.h"
class FetchUnit
{
    Memory *memory;

public:
    FetchUnit(string fn);
    ~FetchUnit();
    Instruction *fetchInstruction(unsigned int pc);
};