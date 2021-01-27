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
    cout << endl << "*************** Algorithm Statistic ****************" << endl;
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



//******************************************************************************
//          returnOverallStats
//******************************************************************************
overStat retStat(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs)
{
    overStat retValue;
 
    float aveOverRes = float(totalResponseTime)/numProcessedJobs;
    float aveOverTurn =float(totalTurnarounTime)/numProcessedJobs;
    float aveOverWait = float(totalWaitTime)/numProcessedJobs;
    float aveOverThrough = float(numProcessedJobs)/100;
    
    retValue.AveResponseTime = aveOverRes;
    retValue.AveTurnaroundTime = aveOverTurn;
    retValue.AveWaitTime = aveOverWait;
    retValue.AveThroughput = aveOverThrough;
    
    return retValue;
}

//******************************************************************************
//          returnOverallStats
//******************************************************************************
overStat retStat(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs, int completedJob)
{
    overStat retValue;
 
    float aveOverRes = float(totalResponseTime)/numProcessedJobs;
    float aveOverTurn =float(totalTurnarounTime)/numProcessedJobs;
    float aveOverWait = float(totalWaitTime)/numProcessedJobs;
    float aveOverThrough = float(completedJob)/100;
    
    retValue.AveResponseTime = aveOverRes;
    retValue.AveTurnaroundTime = aveOverTurn;
    retValue.AveWaitTime = aveOverWait;
    retValue.AveThroughput = aveOverThrough;
    
    return retValue;
}


//******************************************************************************
//          printOverallAlgoStats
//******************************************************************************
void printOverStat(struct overStat stat)
{
    float totalAveResponseTime = stat.AveResponseTime;
    float totalAveTurnaroundTime = stat.AveTurnaroundTime;
    float totalAveWaitTime = stat.AveWaitTime;
    float totalAveThroughput = stat.AveThroughput;
    
    cout << endl << "*************** Overall Average Algorithm Statistic ****************" << endl;
    cout << "Overall Average ResponseTime: " << totalAveResponseTime/5 << endl;
    cout << "Overall Average TurnaroundTime: " << totalAveTurnaroundTime/5 << endl;
    cout << "Overall Average WaitTime: " << totalAveWaitTime/5 << endl;
    cout << "Overall Throughput: " << totalAveThroughput/5 << endl;
    cout << endl ;
}


//******************************************************************************
//          printAlgoStats
//******************************************************************************
void printAlgoStats(int totalResponseTime, int totalTurnarounTime, int totalWaitTime, int numProcessedJobs, int completedJobs)
{
    cout << endl << "*************** Algorithm Statistic ****************" << endl;
    cout << "Average ResponseTime: " << float(totalResponseTime)/numProcessedJobs << endl;
    cout << "Average TurnaroundTime: " << float(totalTurnarounTime)/numProcessedJobs << endl;
    cout << "Average WaitTime: " << float(totalWaitTime)/numProcessedJobs << endl;
    cout << "Throughput: " << float(completedJobs)/100 << endl;
    cout << endl ;
}
