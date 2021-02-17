#include <iostream>
#include "IQueue.h"

using namespace std;

IQ::IQ()
{
}

IQ::~IQ()
{
}

void IQ::printIQ()
{

    cout << "------------------------Instruction Queue------------------------" << endl;
    cout << "type\topcode\tdest\tSrc1\tSrc2\tImm\tAddr\tUserImm" << endl;

    for (unsigned int i = 0; i < iqueue.size(); i++)
    {
        bool op = iqueue[i].ins->getOpcodeValidity();
        bool dest = iqueue[i].ins->getDestValidity();
        bool s1 = iqueue[i].ins->getSrc1Validity();
        bool s2 = iqueue[i].ins->getSrc2Validity();
        bool im = iqueue[i].ins->getImmediateValidity();
        bool addr = iqueue[i].ins->getAddressValidity();
        bool uim = iqueue[i].ins->getUserImmValidity();
        cout << hf.toDecimal(iqueue[i].ins->getType()) << '\t';
        (!op) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getOpcode()) << '\t';
        (!dest) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getDest()) << '\t';
        (!s1) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getSrc1()) << '\t';
        (!s2) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getSrc2()) << '\t';
        (!im) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getImmediate()) << '\t';
        (!addr) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getAddress()) << '\t';
        (!uim) ? cout << " \t" : cout << hf.toDecimal(iqueue[i].ins->getUserImm()) << '\t';
        cout << endl;
    }
    cout << "-----------------------------------------------------------------" << endl;
}

/*
    returns true on successfull insertion to queue
    returns false when queue is full;
*/
bool IQ::push(Instruction *ins, unsigned int id)
{
    if (iqueue.size() < MAX_SIZE)
    {
        iqueue.push_back(qNode{ins, id});
        return true;
    }

    return false;
}

void IQ::pop()
{
    iqueue.erase(iqueue.begin());
}

Instruction *IQ::front()
{

    return iqueue.front().ins;
}

Instruction* IQ::find(unsigned int index){
    return iqueue[index].ins;
}

bool IQ::isEmpty()
{
    return iqueue.empty();
}

unsigned int IQ::getSize(){
    return iqueue.size();
}

