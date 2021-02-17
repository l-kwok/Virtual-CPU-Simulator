#include <iostream>
#include <vector>
#include <chrono>
// #include "memory.h"
#include "Pipline.h"

using namespace std;

int main()
{
    while (true)
    {
        Pipeline p;

        while (!p.execution_status())
        {
            p.fetch();
            p.execute();
            p.commit();
        }
    }

    return 0;
}