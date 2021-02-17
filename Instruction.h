#ifndef _INSTRUCTION_
#define _INSTRUCTION_

#include <vector>
#include "HelperFunctions.h"

using namespace std;
/*
    Instruction class:
    - Implements the properties of the TFO ISA
    - 4 Instruction Types: R, I, J, P
    - Decodes the Instruction
        - ie. converts to binary and separates respective fields (opcode, type, dest, etc...)
        - unitinalized fields (type and opcode are always intialized, dest, src1, src2 etc.. might not be) 
            are indicated with a 2, otherwise binary.
*/
class Instruction
{
    HelperFunctions hf;

    unsigned int numeric_ins;                                                          //numeric form of the Instruction
    vector<unsigned int> binary_ins;                                                   //binary form of Instruction (unformated)
    vector<unsigned int> type, opcode, dest, src1, src2, immediate, address, user_imm; //2 if unset, otherwise binary

    //The index of the starting location of the specified Instruction
    const unsigned int type_start = 0;
    const unsigned int opcode_start = 2;
    const unsigned int dest_start = 6;
    const unsigned int src1_start = 11;
    const unsigned int src2_start = 16;
    const unsigned int immediate_start = 16;
    const unsigned int address_start = 2;
    const unsigned int user_imm_start = 11;
    //Tracks which parts of the instruction is initialized
    bool type_set;
    bool op_set;
    bool dest_set;
    bool src1_set;
    bool src2_set;
    bool imm_set;
    bool addr_set;
    bool uimm_set;

public:
    Instruction(unsigned int ins);
    vector<unsigned int> getType() { return type; };
    vector<unsigned int> getOpcode() { return opcode; };
    vector<unsigned int> getDest() { return dest; };
    vector<unsigned int> getSrc1() { return src1; };
    vector<unsigned int> getSrc2() { return src2; };
    vector<unsigned int> getImmediate() { return immediate; };
    vector<unsigned int> getAddress() { return address; };
    vector<unsigned int> getUserImm() { return user_imm; };

    bool getTypeValidity() { return type_set; };
    bool getOpcodeValidity() { return op_set; };
    bool getDestValidity() { return dest_set; };
    bool getSrc1Validity() { return src1_set; };
    bool getSrc2Validity() { return src2_set; };
    bool getImmediateValidity() { return imm_set; };
    bool getAddressValidity() { return addr_set; };
    bool getUserImmValidity() { return uimm_set; };

private:
    vector<unsigned int> toBinary(unsigned int n);
    void decode();                   //main decode function
    void decode_R();                 //R-Type Decoder
    void decode_I();                 //I-Type Decoder
    void decode_J();                 //J-Type Decorder
    void decode_P(unsigned int val); //P-Type Decorder
};

#endif