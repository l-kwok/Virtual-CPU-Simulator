
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Memory.h"

using namespace std;

Memory::Memory(string filename)
{
    parseCSV(filename);
    cout<<"Thank You. Processing..."<<endl;
    load();
}

Memory::~Memory()
{
    //clean up Memory
    for (unsigned int i = 0; i < instruction_memory.size(); i++)
    {
        delete instruction_memory[i];
    }
}
/*
    Parses the CSV input file:
    - Parses String input and converts to unsigned int
    - Pushes value into "ins" vector
*/
void Memory::parseCSV(string filename)
{
    fstream file;

    file.open(filename, ios::in);
    string line, word;
    if (file.good())
    {
        cout<<"Reading File "<<filename<<endl<<endl;
        while (getline(file, line))
        {
            stringstream ss(line);
            while (getline(ss, word, ','))
            {
                ins.push_back(stoul(word));
            }
        }
    }
}

/*
    Loads "Memory"
    - calls Instruction class to convert unsigned int (ie 34345636) to binary
    - separates binary into respective ISA type (R, I, J, P)
*/
void Memory::load()
{
    for (unsigned int i = 0; i < ins.size(); i++)
    {
        instruction_memory.push_back(new Instruction(ins[i]));
    }
}

vector<unsigned int> Memory::getIns()
{
    return ins;
}

vector<Instruction *> Memory::getDecodedIns()
{
    return instruction_memory;
}
