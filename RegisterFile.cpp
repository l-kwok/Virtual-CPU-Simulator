#include "RegisterFile.h"
#include <iostream>

using namespace std;

RegisterFile::RegisterFile()
{
    for (unsigned int i = 0; i < 15; i++){
        if(i == 0){
            registers.insert(make_pair(i, make_pair((unsigned int)0, true)));  //Registers<key, data(data, valid)>
        } else {
            registers.insert(make_pair(i, make_pair((unsigned int)0, false)));  //Registers<key, data(data, valid)>
        }
    }
}

unsigned int RegisterFile::getRegisterData(unsigned int reg)
{
    return registers.find(reg)->second.first;
}

bool RegisterFile::getRegisterValidity(unsigned int reg)
{
    return (registers.find(reg)->second).second;
}

bool RegisterFile::setRegister(unsigned int reg, unsigned int data, unsigned int ins_type)
{
    if (reg != 0 && reg != 2)  //R0 is READ ONLY, R2 is READ only unless instruction is P-Type
    {
        registers.find(reg)->second.first = data;
        // cout<<"reg: "<<reg<<"reg set: "<< registers.find(reg)->second.first << " Data: "<<data<<endl;
        registers.find(reg)->second.second = true;
        return true;
    }

    if (reg == 2 && ins_type == 3)  //3 = P-Type Instruction, only P-Type can WRITE to R2
    {
        registers.find(reg)->second.first = data;
        registers.find(reg)->second.second = true;
        return true;
    }

    return false;
}

void RegisterFile::printStack(){
    cout << "--------------------Register Stack--------------------" << endl;
    for(size_t i = 0; i < 15; i++){
        cout <<"R"<<i<<": "<<registers.find(i)->second.first << " Valid: "<<registers.find(i)->second.second<<endl; 
    }
}