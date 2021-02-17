#include <iostream>

using namespace std;

class Stats
{
    unsigned int throughput;
    unsigned long long total_time;
    double avg_lat;
public:
    Stats(unsigned int fetch_width, unsigned int issue_width, unsigned int commit_width);
    void calculateLatency(unsigned long long start, unsigned long long end, unsigned int num_ins);
    void printStats();
};