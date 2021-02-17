#include <iostream>
#include <fstream>
#include <chrono>
#include "Pipline.h"

using namespace std;

static unsigned long long current_millis()
{
    // code stolen from https://stackoverflow.com/a/56107709
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Pipeline::Pipeline()
{
    PC = 0; //Program Counter
    ins_num = 0; //Number of instructions
    statistics = new Stats(FETCH_WIDTH, ISSUE_WIDTH, COMMIT_WIDTH);
    fstream file;
    cout << "Enter Program Name: ";
    cin >> filename;

    if (filename.compare("exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }

    if (filename.size() < 5)
    {
        filename.append(".csv");
    }
    else if ((filename.substr(filename.size() - 4)).compare(".csv") != 0)
    {
        filename.append(".csv");
    }

    file.open(filename, ios::in);

    while (!file.good())
    {
        cout << "File \"" << filename << "\" Failed To Open: Make Sure The File Exists." << endl;
        cout << "Enter Program Name: ";
        cin >> filename;

        if (filename.size() < 5)
        {
            filename.append(".csv");
        }
        else if ((filename.substr(filename.size() - 4)).compare(".csv") != 0)
        {
            filename.append(".csv");
        }

        file.open(filename, ios::in);
    }
    FU = new FetchUnit(filename);
    start_time = current_millis();
}

Pipeline::~Pipeline()
{
    delete FU;
    delete statistics;
}

void Pipeline::fetch()
{
    for (unsigned int i = 0; i < FETCH_WIDTH; i++)
    {
        Instruction *curr_ins = FU->fetchInstruction(PC);
        // vector<unsigned int> temp = curr_ins->getOpcode();
        // for(size_t i = 0; i < curr_ins->getOpcode().size(); i++){
        //     cout<<temp[i];
        // }
        // cout<<endl;

        if (curr_ins == nullptr)
            return; //no more instructions left

        if (!iq.push(curr_ins, ins_num))
            return; //IQ is full

        if (ROB.size() < MAX_SIZE)
        {
            ROB.push_back(ROB_node{
                curr_ins, //Instruction Object
                false,    //Validity Bit
                ins_num        //ROB ID
            });
        }
        else
        {
            return; //ROB is full
        }
        // iq.printIQ(); //DEBUGGING
        ins_num += 1;
        PC += 1;
    }
}

void Pipeline::execute()
{
    if (execution_finished)
        return;
    // cout << "--------------------Execute--------------------" << endl;
    for (unsigned int i = 0; i < ISSUE_WIDTH; i++)
    {
        if (i < iq.getSize()) //prevents executing instructions beyong what exists in the IQ
        {
            Instruction *curr_ins = iq.find(i);
            unsigned int type = hf.toDecimal(curr_ins->getType());
            switch (type)
            {
            case 0:
                // cout << "Executing R instruction..." << endl;
                if (execute_r(curr_ins))
                {
                    ROB[i].valid = true;
                }
                break;
            case 1:
                // cout << "Executing I instruction..." << endl;
                if (execute_i(curr_ins))
                {
                    ROB[i].valid = true;
                }
                break;
            case 2:
                // cout << "Executing j instruction..." << endl;
                if (execute_j(curr_ins))
                {
                    ROB[i].valid = true;
                }
                break;
            case 3:
                // cout << "Executing P instruction..." << endl;
                if (execute_p(curr_ins))
                {
                    ROB[i].valid = true;
                }
                break;
            }
            // registers.printStack();
        }
    }
}

void Pipeline::commit()
{
    if (execution_finished){
        end_time = current_millis();
        statistics->calculateLatency(start_time, end_time, ins_num);
        statistics->printStats();
    }
        
    // cout << "--------------------Commit---------------------" << endl;
    for (unsigned int i = 0; i < COMMIT_WIDTH; i++)
    {

        if (ROB.empty())
            return;
        if (ROB.front().valid == true)
        {
            // cout << "Committing ROB ID: " << ROB.front().rob_id << endl;
            ROB.erase(ROB.begin());
        }
        if (iq.isEmpty())
            return;
        iq.pop();
    }
}

bool Pipeline::execute_p(Instruction *ins)
{
    //we have opcode but we dont need it... nice
    // unsigned int opcode = hf.toDecimal(ins->getOpcode());
    unsigned int dest = hf.toDecimal(ins->getDest());
    unsigned int imm = hf.toDecimal(ins->getUserImm());

    //cheating a bit here, the set Register function automatically sets validity on sucessful register find
    bool isSet = registers.setRegister(dest, imm, hf.toDecimal(ins->getType()));
    if (isSet)
    {
        // cout << "P-Type Instruction Executed Sucessfully" << endl;
        return true;
    }
    else
    {
        // cout << "P-Type Instruction Failed: No access to register" << endl;
        return false;
    }
}

bool Pipeline::execute_r(Instruction *ins)
{
    unsigned int opcode = hf.toDecimal(ins->getOpcode());
    unsigned int dest = hf.toDecimal(ins->getDest());
    unsigned int src1 = hf.toDecimal(ins->getSrc1());
    unsigned int src2 = hf.toDecimal(ins->getSrc2());
    bool isSet = false;
    unsigned int result = ALU.executeOperation(opcode, registers.getRegisterData(src1), registers.getRegisterData(src2));

    if (opcode == 8)
    {
        cout << "Final Result is: " << registers.getRegisterData(dest) << endl;
        isSet = true;
        execution_finished = true;
    }
    else
    {
        isSet = registers.setRegister(dest, result, hf.toDecimal(ins->getType()));
    }

    if (isSet)
    {
        // cout << "R-Type Instruction Executed Sucessfully" << endl;
        return true;
    }
    else
    {
        // cout << "R-Type Instruction Failed" << endl;
        return false;
    }
}

bool Pipeline::execute_i(Instruction *ins)
{
    unsigned int opcode = hf.toDecimal(ins->getOpcode());
    unsigned int dest = hf.toDecimal(ins->getDest());
    unsigned int imm = hf.toDecimal(ins->getImmediate());
    unsigned int src1 = hf.toDecimal(ins->getSrc1());
    bool isSet = false;
    unsigned int result = ALU.executeOperation(opcode, registers.getRegisterData(src1), imm);
    //    cout<<"Imm:"<<imm<<" src1: "<<src1<<"data:"<<registers.getRegisterData(src1)<<"calc: "<<result<<endl;
    //branches
    if (opcode == 5 || opcode == 6)
    {
        result = ALU.executeOperation(opcode, registers.getRegisterData(dest), registers.getRegisterData(src1));
        if (result == 1)
        {
            //NOTE: Issue with Fetch Width: What if its already in the iq/ROB?
            //Solution: Clear the ROB and IQ and refetch in the next clock cycle
            ROB.clear();
            iq.clear();
            PC = imm;
            isSet = true;
        }
        else
        {
            isSet = true;
        }
    }
    else
    {
        isSet = registers.setRegister(dest, result, hf.toDecimal(ins->getType()));
    }

    if (isSet)
    {
        // cout << "I-Type Instruction Executed Sucessfully" << endl;
        return true;
    }
    else
    {
        // cout << "I-Type Instruction Failed" << endl;
        return false;
    }
}

bool Pipeline::execute_j(Instruction *ins)
{
    bool isSet = false;
    if (isSet)
    {
        // cout << "I-Type Instruction Executed Sucessfully" << endl;
        return true;
    }
    else
    {
        // cout << "I-Type Instruction Failed" << endl;
        return false;
    }
}

bool Pipeline::ROB_isEmpty()
{
    if (ROB.size() == 0)
    {
        return true;
    }
    return false;
}