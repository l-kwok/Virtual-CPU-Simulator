#include <string>
#include <vector>
#include "Instruction.h"

using namespace std;


/*
    Memory Class: 
    - implements the properties of "Memory"
    - Stores all the Instructions to be executed
    - Parses input program (.csv files)
    - Initializes and decodes Instructions (through Instruction.h)
*/
class Memory
{
    const unsigned int FETCH_WIDTH = 1;
    vector<unsigned int> ins; //List in Integer Form of the Instructions
    vector<Instruction*> instruction_memory; //List in Instruction Object Form of the instructions
public:
    ~Memory();
    Memory(string filename);
    vector<unsigned int> getIns(); //gets the list of integer form instructions
    vector<Instruction*> getDecodedIns();
private:
    void parseCSV(string filename);
    void load(); //loads memory


};