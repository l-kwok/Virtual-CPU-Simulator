#include <vector>
#include "RegisterFile.h"
#include "FetchUnit.h"
#include "IQueue.h"
#include "Execute.h"
#include "Stats.h"

using namespace std;

class Pipeline
{
    struct ROB_node //Node for ROB list
    {
        Instruction *ins;
        bool valid;
        unsigned int rob_id;
    };
    const unsigned int FETCH_WIDTH = 10;
    const unsigned int ISSUE_WIDTH = 20;
    const unsigned int COMMIT_WIDTH = 9;

    const unsigned int MAX_SIZE = 20;
    unsigned int PC;        // Program Counter
    FetchUnit *FU;          // Instantiates/Loads Memory and Instructions
    RegisterFile registers; // Contains all the registers and their data
    Execute ALU;            // Arithmetic Logic Unit
    vector<ROB_node> ROB;   // Reorder Buffer
    IQ iq;                  // IQueue
    HelperFunctions hf;
    Stats *statistics;
    string filename;
    bool execution_finished = false;
    unsigned long long start_time;
    unsigned long long end_time;
    unsigned int ins_num;

public:
    Pipeline();
    ~Pipeline();
    void fetch();
    void execute();
    void commit();
    bool ROB_isEmpty();
    bool execution_status() { return execution_finished; };

private:
    bool execute_p(Instruction *ins);
    bool execute_r(Instruction *ins);
    bool execute_i(Instruction *ins);
    bool execute_j(Instruction *ins);
};