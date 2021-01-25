//
//  stats.cpp
//  Project_2_AT
//
//  Created by Anh Tuk on 1/24/21.
//

#include "stats.hpp"


//******************************************************************************
//          printStats
//******************************************************************************
void printStats(Node * currentNode)
{
    cout << "Name: " << currentNode->getJob().getName()
    << "\nResponseTime: " << currentNode->getJob().getRes()
    << "\nTurnaroundTime: " << currentNode->getJob().getTurn()
    << "\nWaitTime: " << currentNode->getJob().getWait()
    << endl << endl;
}


//******************************************************************************
//          printAlgoStats
//******************************************************************************
void printAlgoStats(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs)
{
    cout << "*************** Algorithm Statistic ****************" << endl;
    cout << "Average ResponseTime: " << float(totalResponseTime)/numProcessedJobs << endl;
    cout << "Average TurnaroundTime: " << float(totalTurnarounTime)/numProcessedJobs << endl;
    cout << "Average WaitTime: " << float(totalWaitTime)/numProcessedJobs << endl;
    cout << "Throughput: " << float(numProcessedJobs)/100 << endl;
    cout << endl ;
}

//******************************************************************************
//          printTimeChart
//******************************************************************************

void printTimeChart(List finishedQueue)
{
    cout << endl << "*************** Time Chart for 100 Quanta ****************" << endl;
    while(finishedQueue.getHead() != nullptr)
    {
        int startTime = finishedQueue.getHead()->getJob().getArr()+finishedQueue.getHead()->getJob().getRes();
        while(startTime > 0)
        {
            cout << ".";
            startTime--;
        }
        cout << finishedQueue.getHead()->getJob().getName() << endl;
        
        finishedQueue.getHead()->getJob();
        finishedQueue.deleteHeadNode();
    }
    cout << endl << endl;
}

