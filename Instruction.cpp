#include <iostream>
#include "Instruction.h"

using namespace std;

Instruction::Instruction(unsigned int ins)
{

    numeric_ins = ins;
    type_set = true;
    op_set = false;
    dest_set = false;
    src1_set = false;
    src2_set = false;
    imm_set = false;
    addr_set = false;
    uimm_set = false;
    decode();
}

void Instruction::decode()
{
    binary_ins = hf.toBinary(numeric_ins);

    // for(unsigned int i = 0; i < binary_ins.size(); i++){
    //     cout<<binary_ins[i];
    // }
    // cout<<endl;


    //define type
    type.push_back(binary_ins[0]);
    type.push_back(binary_ins[1]);
    if (binary_ins[0] == 0)
    {
        if (binary_ins[1] == 0)
        {
            //00: R-Type
            // cout << "R-TYPE"<<endl;
            decode_R();
        }
        else
        {
            //01: I-Type
            // cout << "I-TYPE"<<endl;
            decode_I();
        }
    }
    else
    {
        if (binary_ins[1] == 0)
        {
            //10: J-Type
            // cout << "J-TYPE"<<endl;
            decode_J();
        }
        else
        {
            //11: P-Type
            // cout << "P-TYPE"<<endl;
            unsigned int val = 0;
            cout << "Enter a parameter for execution: ";
            cin >> val;
            cout<<endl;
            decode_P(val);
        }
    }
}



void Instruction::decode_R()
{
    op_set = true;
    dest_set = true;
    src1_set = true;
    src2_set = true;

    for (unsigned int i = opcode_start; i < opcode_start + 4; i++)
    {
        opcode.push_back(binary_ins[i]);
    }

    for (unsigned int i = dest_start; i <  dest_start + 5; i++)
    {
        dest.push_back(binary_ins[i]);
    }

    for (unsigned int i = src1_start; i < src1_start + 5; i++)
    {
        src1.push_back(binary_ins[i]);
    }

    for (unsigned int i = src2_start; i < src2_start + 5; i++)
    {
        src2.push_back(binary_ins[i]);
    }
}

void Instruction::decode_I()
{
    op_set = true;
    dest_set = true;
    src1_set = true;
    imm_set = true;

    for (unsigned int i = opcode_start; i < opcode_start + 4; i++)
    {
        opcode.push_back(binary_ins[i]);
    }

    for (unsigned int i = dest_start; i < dest_start + 5; i++)
    {
        dest.push_back(binary_ins[i]);
    }

    for (unsigned int i = src1_start; i < src1_start + 5; i++)
    {
        src1.push_back(binary_ins[i]);
    }

    for (unsigned int i = immediate_start; i < immediate_start + 16; i++)
    {
        immediate.push_back(binary_ins[i]);
    }
}

void Instruction::decode_J()
{
    addr_set = true;
    for (unsigned int i = address_start; i < binary_ins.size(); i++)
    {
        address.push_back(binary_ins[i]);
    }
}

void Instruction::decode_P(unsigned int val)
{
    op_set = true;
    dest_set = true;
    uimm_set = true;

    for (unsigned int i = opcode_start; i < opcode_start + 4; i++)
    {
        opcode.push_back(binary_ins[i]);
    }

    for (unsigned int i = dest_start; i < dest_start + 5; i++)
    {
        dest.push_back(binary_ins[i]);
    }

    vector<unsigned int> n = hf.toBinary(val);
    for (unsigned int i = n.size()-1; i > 20; --i)
    {
        user_imm.insert(user_imm.begin(), n[i]);
    }
}