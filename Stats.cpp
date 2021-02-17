#include <iostream>
#include "Stats.h"

using namespace std;

Stats::Stats(unsigned int fw, unsigned int iw, unsigned int cw)
{
    unsigned int min = fw;
    if (iw < min)
    {
        min = iw;
    }

    if (cw < min)
    {
        min = cw;
    }
    throughput = min;
    avg_lat = 0;
}

void Stats::calculateLatency(unsigned long long start, unsigned long long end, unsigned int num_ins){
    double end_conv = (unsigned long long) end;
    double start_conv = (unsigned long long) start;
    avg_lat = (end_conv-start_conv)/num_ins;
}

void Stats::printStats(){
    cout<<"Average Latency Per Insruction: "<<avg_lat<<"ms"<<endl;
    cout<<"Average Throughput Per Instruction: "<<throughput<<endl;
}