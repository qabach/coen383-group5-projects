//
//  stats.hpp
//  Project_2_AT
//
//  Created by Anh Tuk on 1/24/21.
//

#include <stdio.h>
#include <iostream>
#include "linked.hpp"
using namespace std;


#ifndef stats_hpp
#define stats_hpp

struct overStat{
    float AveWaitTime = 0;
    float AveResponseTime = 0;
    float AveTurnaroundTime = 0;
    float AveThroughput = 0;
};

void printStats(Node * currentNode);
void printAlgoStats(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs);
void printTimeChart(List finishedQueue);
overStat retStat(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs);
void printOverStat(struct overStat stat);

#endif /* stats_hpp */
