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

void printStats(Node * currentNode);
void printAlgoStats(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs);
void printTimeChart(List finishedQueue);


#endif /* stats_hpp */
