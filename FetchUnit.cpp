#include <iostream>
#include "FetchUnit.h"

using namespace std;

FetchUnit::FetchUnit(string fn)
{
    memory = new Memory(fn);
}

FetchUnit::~FetchUnit()
{
    delete memory;
}

Instruction *FetchUnit::fetchInstruction(unsigned int pc)
{
    vector<Instruction *> instructions = memory->getDecodedIns();
    if (pc < instructions.size())
        return instructions[pc]; //return the instruction
    else
        return nullptr; //no instructions left
}