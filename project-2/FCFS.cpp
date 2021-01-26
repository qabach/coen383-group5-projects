//
//  FCFS.cpp
//  Project_2_AT
//
//  Created by Anh Tuk on 1/23/21.
//

#include <iostream>
#include "FCFS.hpp"
#include "stats.hpp"


void FCFS(List * processQueue)
{
    cout << "******************** FCFS ********************" << endl;
    
    
    
    Node * currentNode = NULL;
    currentNode = processQueue->getHead();
    
    int numProcessedJobs = 0;

    double totalResponseTime = 0;
    double totalWaitTime = 0;
    double totalTurnarounTime = 0;
    
    List finishedQueue;
    finishedQueue = List();
   
    
    int timeslice = 0;  // to keep track of the timeslice
    
    //while(currentNode->getJob().getArr() <= 99 and processQueue != nullptr)
    while(currentNode != nullptr && timeslice < 100)
    {
        
        cout << endl << "Current time: " << timeslice << endl;
        currentNode->printData();
        cout << endl;
        
        if (timeslice < currentNode->getJob().getArr())        // job cannot arrive before the passing of time
        {
            timeslice++;
        }
        
        else
        {
            int responseTime = timeslice - currentNode->getJob().getArr();
            //currentNode->getJob().setRes(responseTime);
            //cout << "responseTime: " << responseTime << endl;
            totalResponseTime += responseTime;
            
            
            timeslice += currentNode->getJob().getServ();
            
            int turnaroundTime = timeslice - currentNode->getJob().getArr();
            //currentNode->getJob().setTurn(turnaroundTime);
            //cout << "turnaround: " << turnaroundTime << endl;
            totalTurnarounTime += turnaroundTime;
            
            
            int waitTime = turnaroundTime - currentNode->getJob().getServ();
            //currentNode->getJob().setWait(waitTime);
            //cout << "waittime: " << waitTime << endl;
            totalWaitTime += waitTime;
            
            
            currentNode->setJobStats(waitTime, responseTime, turnaroundTime);
            
            numProcessedJobs++;
            //cout << "num Jobs Processed: " << numProcessedJobs << endl;
            
            printStats(currentNode);
            
         
            finishedQueue.pushDataNS(currentNode->getJob());
            processQueue->deleteHeadNode();
            cout << "Processed Queue: " << endl;
            finishedQueue.printListOnlyName();
            currentNode = processQueue->getHead();
            
        }
       
    }
    
    printTimeChart(finishedQueue);
    
    printAlgoStats(totalResponseTime, totalTurnarounTime, totalWaitTime, numProcessedJobs);
    
}
